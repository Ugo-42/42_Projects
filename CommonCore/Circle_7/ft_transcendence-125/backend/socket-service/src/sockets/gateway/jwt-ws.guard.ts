import {
	CanActivate,
	ExecutionContext,
	Injectable,
	UnauthorizedException,
} from '@nestjs/common';

import { JwtService } from '@nestjs/jwt';
import { Socket } from 'socket.io';
import { JwtPayload } from '../interfaces/jwt-payload.interface'


@Injectable()
export class JwtWsGuard implements CanActivate {

	constructor(
		private readonly jwtService: JwtService,
	) {}


	canActivate(
		context: ExecutionContext,
	): boolean {

		const client =
			context
				.switchToWs()
				.getClient<Socket>();

		/*
		 * Récupération du JWT.
		 *
		 * Ordre :
		 * 1. Authorization: Bearer <token>
		 * 2. Socket.IO auth.token
		 * 3. query ?token=<token>
		 */
		const token =
			client.handshake.headers.authorization
				?.replace(/^Bearer\s+/i, '') ||
			client.handshake.auth?.token ||
			client.handshake.query.token;


		if (
			!token ||
			typeof token !== 'string'
		) {
			throw new UnauthorizedException(
				'Missing WebSocket token',
			);
		}


		try {

			/*
			 * Vérification du JWT.
			 *
			 * Le payload est stocké dans le socket
			 * afin que les handlers puissent récupérer
			 * l'utilisateur authentifié.
			 */

			const payload =
   				this.jwtService.verify<JwtPayload>(token)

			client.data.user = payload;

			return true;

		} catch {

			throw new UnauthorizedException(
				'Invalid WebSocket token',
			);
		}
	}
}
