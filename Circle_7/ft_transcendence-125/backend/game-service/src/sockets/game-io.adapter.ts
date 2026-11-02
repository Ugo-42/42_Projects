import { INestApplicationContext } from '@nestjs/common'
import { IoAdapter } from '@nestjs/platform-socket.io'
import { ServerOptions } from 'socket.io'

export class GameIoAdapter extends IoAdapter {

	constructor(
		app: INestApplicationContext,
	) {
		super(app)
	}

	createIOServer(
		port: number,
		options?: ServerOptions,
	) {
		return super.createIOServer(
			port,
			{
				...options,
				path: '/game-socket.io',
			},
		)
	}
}