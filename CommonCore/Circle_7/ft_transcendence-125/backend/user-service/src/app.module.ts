import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AuthModule } from './auth-service/auth.module';

import { ProfileModule } from './profile/profile.module';
import { UserModule } from './user/user.module';
import { FriendsModule } from './friends/friends.module';

@Module({
  imports: [AuthModule, ProfileModule, UserModule, FriendsModule],
  controllers: [AppController],
  providers: [],
})
export class AppModule {}
