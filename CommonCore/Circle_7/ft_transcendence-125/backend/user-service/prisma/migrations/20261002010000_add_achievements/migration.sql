CREATE TYPE "AchievementType" AS ENUM ('PLAY_GAME', 'WIN_GAME', 'PLACE_10_BOMBS');

CREATE TABLE "UserAchievement" (
    "id" SERIAL NOT NULL,
    "userId" INTEGER NOT NULL,
    "type" "AchievementType" NOT NULL,
    "rewardXp" INTEGER NOT NULL,
    "unlockedAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT "UserAchievement_pkey" PRIMARY KEY ("id")
);

CREATE UNIQUE INDEX "UserAchievement_userId_type_key" ON "UserAchievement"("userId", "type");
CREATE INDEX "UserAchievement_userId_idx" ON "UserAchievement"("userId");
ALTER TABLE "UserAchievement" ADD CONSTRAINT "UserAchievement_userId_fkey"
    FOREIGN KEY ("userId") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE;
