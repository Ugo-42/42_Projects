import { NestFactory } from '@nestjs/core';
import { ValidationPipe, BadRequestException } from '@nestjs/common';
import { AppModule } from './app.module';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);

  app.enableCors({
    origin: true,
    credentials: true,
  });

  app.useGlobalPipes(
    new ValidationPipe({
      transform: true,
      whitelist: true,
      forbidNonWhitelisted: true,
      exceptionFactory: () => new BadRequestException('Invalid input'),
    }),
  );

  app.enableShutdownHooks();

  const port = process.env.PORT;
  if (!port) {
    throw new Error('PORT environment variable is not defined');
  }
  await app.listen(port);
  console.log(`Service is running on port: ${port}`);
}
bootstrap();

