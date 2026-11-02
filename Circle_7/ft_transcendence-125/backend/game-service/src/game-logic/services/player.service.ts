import { Injectable } from '@nestjs/common';
import { Player, PlayerColor } from '../models/player';
import { PowerUpType } from '../models/power-up';
import { GameState } from '../models/game-state';

@Injectable()
export class PlayerService {
	// Cree un nouveau joueur
	createPlayer(
		game: GameState,
		id: number,
		username: string,
		color: PlayerColor,
		x: number,
		y: number,
	): Player {
		const player = new Player(
			id,
			username,
			color,
			x,
			y,
		);

		game.players.set(id, player);

		return player;
	}

	// Supprime un joueur
	removePlayer(game: GameState, id: number): boolean {
		return game.players.delete(id);
	}

	// Recupere un joueur
	getPlayer(game: GameState, id: number): Player | undefined {
		return game.players.get(id);
	}

	// Verifier si un joueur existe
	hasPlayer(game: GameState, id: number): boolean {
		return game.players.has(id);
	}

	// Recupere tous les joueurs
	getPlayers(game: GameState): Player[] {
		return Array.from(game.players.values());
	}

	// Nombre de joueurs actuellement presents
	getPlayerCount(game: GameState): number {
		return game.players.size;
	}

	// Supprime tous les joueurs
	clearPlayers(game: GameState): void {
		game.players.clear();
	}

	getAlivePlayers(state: GameState): Player[] {
		return this.getPlayers(state).filter((p) => p.alive);
	}

	// Applique un powerup au joueur
	applyPowerUp(
		game: GameState,
		playerId: number,
		powerUp: PowerUpType,
	): boolean {
		const player = this.getPlayer(game, playerId);

		if (!player || !player.alive) {
			return false;
		}
		
		switch (powerUp) {
			case PowerUpType.BOMB_PLUS:
				player.maxBombs++;
				player.availableBombs++;
				break;
			case PowerUpType.BOMB_MINUS:
				player.maxBombs = Math.max(1, player.maxBombs - 1);
				player.availableBombs = Math.min(player.availableBombs, player.maxBombs);
				break;
			case PowerUpType.KICK:
				player.canKickBombs = true;
				break;
			case PowerUpType.SPEED_PLUS:
				player.speed++;
				break;
			case PowerUpType.SPEED_MINUS:
				player.speed = Math.max(1, player.speed - 1);
				break;
			case PowerUpType.FLAME_PLUS:
				player.flameRange++;
				break;
			case PowerUpType.FLAME_MINUS:
				player.flameRange = Math.max(1, player.flameRange - 1);
				break;
			default:
				return false;
		}

		player.stats.powerUpsCollected++;
		return true;
	}
}
