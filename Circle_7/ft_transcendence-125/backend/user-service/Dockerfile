FROM node:20-alpine AS builder

WORKDIR /app

COPY package*.json ./

RUN npm install

COPY . .

# Avoid stale incremental cache causing incomplete dist output in container builds.
RUN rm -f tsconfig.tsbuildinfo

# Prisma client generation
RUN npx prisma generate --schema=prisma/schema.prisma

# Build NestJS
RUN npm run build

FROM node:20-alpine

WORKDIR /app

COPY --from=builder /app/package*.json ./
COPY --from=builder /app/dist ./dist
COPY --from=builder /app/node_modules ./node_modules
COPY --from=builder /app/prisma ./prisma

CMD ["sh", "-c", "npx prisma migrate deploy && node dist/main.js"]
