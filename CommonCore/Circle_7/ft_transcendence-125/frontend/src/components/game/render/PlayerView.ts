/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  PlayerView.ts                                          ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/25 10:03:23 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/30 21:07:38 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import Phaser from "phaser"
import { SCALE, worldToScreen } from "../config/screenConfig"
import { CHARACTER_WALK_FRAMES, CHARACTER_WALK_CYCLE_MS, DIRECTION_ROW } from "../config/characterConfig"
import type { FacingDirection } from "../config/characterConfig"
import { DEATH_TOTAL_FRAMES, DEATH_DURATION_MS, DEATH_TEXTURE_KEY, DEATH_ANIM_KEY } from "../config/deathConfig"

const MOVE_DURATION_MS = 250
const MOVE_EPSILON = 0.5

type TargetPosition = {
	x: number
	y: number
	direction: FacingDirection
}

function walkAnimKey(characterKey: string, direction: FacingDirection): string {
	return `${characterKey}-walk-${direction}`
}

function directionFromDelta(dx: number, dy: number): FacingDirection {
	if (Math.abs(dx) >= Math.abs(dy)) return dx >= 0 ? "right" : "left"
	return dy >= 0 ? "down" : "up"
}

export class PlayerView {
	private sprite: Phaser.GameObjects.Sprite
	private authoritativePosition: { x: number; y: number } | null = null
	private target: TargetPosition | null = null
	private initialized = false
	private facing: FacingDirection = "down"
	private characterKey: string
	private movementAxis: "x" | "y" | null = null
	private moveElapsed = 0
	private moveStart = { x: 0, y: 0 }
	private isDead = false

	static registerAnimations(scene: Phaser.Scene, characterKey: string) {
		(Object.keys(DIRECTION_ROW) as FacingDirection[]).forEach((direction) => {
			const key = walkAnimKey(characterKey, direction)
			if (scene.anims.exists(key)) return
			const row = DIRECTION_ROW[direction]
			const start = row * CHARACTER_WALK_FRAMES
			const end = start + CHARACTER_WALK_FRAMES - 1
			scene.anims.create({ key, frames: scene.anims.generateFrameNumbers(characterKey, { start, end }), frameRate: CHARACTER_WALK_FRAMES / (CHARACTER_WALK_CYCLE_MS / 1000), repeat: -1 })
		})
	}

	static registerDeathAnimation(scene: Phaser.Scene) {
		if (scene.anims.exists(DEATH_ANIM_KEY)) return

		scene.anims.create({
			key: DEATH_ANIM_KEY,
			frames: scene.anims.generateFrameNumbers(DEATH_TEXTURE_KEY, { start: 0, end: DEATH_TOTAL_FRAMES - 1 }),
			frameRate: DEATH_TOTAL_FRAMES / (DEATH_DURATION_MS / 1000),
			repeat: 0,
		})
	}

	constructor(scene: Phaser.Scene, characterKey: string) {
		this.characterKey = characterKey
		const idleFrame = DIRECTION_ROW[this.facing] * CHARACTER_WALK_FRAMES
		this.sprite = scene.add.sprite(0, 0, characterKey, idleFrame).setScale(SCALE)
	}

	render(worldX: number, worldY: number) {
		if (this.isDead) return

		const screen = worldToScreen(worldX, worldY)

		if (!this.initialized) {
			this.sprite.setPosition(screen.x, screen.y)
			this.authoritativePosition = { x: screen.x, y: screen.y }
			this.initialized = true
			return
		}

		if (this.authoritativePosition && Math.abs(screen.x - this.authoritativePosition.x) <= MOVE_EPSILON && Math.abs(screen.y - this.authoritativePosition.y) <= MOVE_EPSILON) return

		const previous = this.authoritativePosition ?? { x: this.sprite.x, y: this.sprite.y }
		const dx = screen.x - previous.x
		const dy = screen.y - previous.y

		this.authoritativePosition = { x: screen.x, y: screen.y }

		if (Math.abs(dx) <= MOVE_EPSILON && Math.abs(dy) <= MOVE_EPSILON) return

		this.movementAxis = Math.abs(dx) >= Math.abs(dy) ? "x" : "y"
		this.moveStart = { x: this.sprite.x, y: this.sprite.y }
		this.moveElapsed = 0

		this.target = {
			x: screen.x,
			y: screen.y,
			direction: directionFromDelta(dx, dy),
		}

		this.startTarget()
	}

	stop() {
		if (!this.target) this.stopWalking()
	}

	update(delta: number) {
		if (this.isDead) return
		if (!this.target) return

		this.moveElapsed += delta
		const progress = Math.min(this.moveElapsed / MOVE_DURATION_MS, 1)

		if (this.movementAxis === "x") {
			this.sprite.x = Phaser.Math.Linear(this.moveStart.x, this.target.x, progress)
			this.sprite.y = this.target.y
		} else {
			this.sprite.x = this.target.x
			this.sprite.y = Phaser.Math.Linear(this.moveStart.y, this.target.y, progress)
		}

		if (progress >= 1) {
			this.finishTarget()
		}
	}

	playDeath(onComplete: () => void) {
		this.isDead = true
		this.target = null
		this.movementAxis = null

		this.sprite.setTexture(DEATH_TEXTURE_KEY, 0)
		this.sprite.play(DEATH_ANIM_KEY)
		this.sprite.once("animationcomplete", () => {
			this.destroy()
			onComplete()
		})
	}

	private startTarget() {
		if (!this.target) return
		this.facing = this.target.direction
		this.sprite.play(walkAnimKey(this.characterKey, this.facing), true)
	}

	private finishTarget() {
		if (!this.target) return
		this.sprite.setPosition(this.target.x, this.target.y)
		this.target = null
		this.movementAxis = null
		this.moveElapsed = 0
		this.stopWalking()
	}

	private stopWalking() {
		this.sprite.stop()
		this.sprite.setFrame(DIRECTION_ROW[this.facing] * CHARACTER_WALK_FRAMES)
	}

	destroy() {
		this.sprite.destroy()
	}
}
