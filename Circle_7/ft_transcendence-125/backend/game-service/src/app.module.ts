import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { PrismaModule } from './prisma/prisma.module';
import { LobbyModule } from './lobby/lobby.module';
import { GameLogicModule } from './game-logic/game-logic.module';
import { GameSocketModule } from './sockets/game-socket.module'

@Module({
    imports: [
        PrismaModule,
        LobbyModule,
        GameLogicModule,
        GameSocketModule,
    ],
    controllers: [
        AppController,
    ],
	providers: [],
})
export class AppModule {}
