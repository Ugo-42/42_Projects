import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { SocketModule } from './sockets/socket.module';

@Module({
  imports: [SocketModule],
  controllers: [AppController],
  providers: [],
})
export class AppModule {}
