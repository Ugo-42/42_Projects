import { Socket } from 'socket.io'

import { JwtPayload } from './jwt-payload.interface'

export interface GameSocketData {
	user: JwtPayload
}

export type AuthenticatedGameSocket = Socket<
	any,
	any,
	any,
	GameSocketData
>