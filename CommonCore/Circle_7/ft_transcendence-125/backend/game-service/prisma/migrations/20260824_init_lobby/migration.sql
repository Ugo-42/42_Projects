-- CreateSchema
CREATE SCHEMA IF NOT EXISTS "public";

-- CreateEnum
CREATE TYPE "LobbyStatus" AS ENUM ('WAITING', 'IN_GAME');

-- CreateTable
CREATE TABLE "Lobby" (
    "id" TEXT NOT NULL,
    "name" TEXT NOT NULL,
    "ownerId" INTEGER NOT NULL,
    "isPrivate" BOOLEAN NOT NULL DEFAULT false,
    "code" TEXT,
    "status" "LobbyStatus" NOT NULL DEFAULT 'WAITING',
    "maxPlayers" INTEGER NOT NULL DEFAULT 4,
    "createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT "Lobby_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "LobbyPlayer" (
    "id" SERIAL NOT NULL,
    "lobbyId" TEXT NOT NULL,
    "userId" INTEGER NOT NULL,
    "username" TEXT NOT NULL,
    "ready" BOOLEAN NOT NULL DEFAULT false,
    "joinedAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT "LobbyPlayer_pkey" PRIMARY KEY ("id")
);

-- CreateIndex
CREATE UNIQUE INDEX "Lobby_code_key" ON "Lobby"("code");

-- CreateIndex
CREATE UNIQUE INDEX "LobbyPlayer_lobbyId_userId_key" ON "LobbyPlayer"("lobbyId", "userId");

-- AddForeignKey
ALTER TABLE "LobbyPlayer" ADD CONSTRAINT "LobbyPlayer_lobbyId_fkey" FOREIGN KEY ("lobbyId") REFERENCES "Lobby"("id") ON DELETE CASCADE ON UPDATE CASCADE;

