import { Injectable } from '@nestjs/common'
import { Player } from '../models/player'

@Injectable()
export class XpService {

	calculate(player: Player): number {
		return (
			player.stats.kills * 100 +
			player.stats.bombsPlaced * 5 +
			player.stats.blocksDestroyed * 5 +
			player.stats.powerUpsCollected * 10 +
			player.stats.gamesWon * 500
		)
	}
}