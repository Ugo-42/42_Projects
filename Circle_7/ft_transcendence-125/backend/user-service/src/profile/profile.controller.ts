import {
    Body,
    Controller,
    Get,
    Param,
    ParseIntPipe,
    Patch,
    Req,
    Res,
    UploadedFile,
    UseGuards,
    UseInterceptors,
    ParseFilePipe,
    MaxFileSizeValidator,
    FileTypeValidator,
} from '@nestjs/common';
import { FileInterceptor } from '@nestjs/platform-express';
import { Response } from 'express';
import { diskStorage } from 'multer';
import { mkdirSync } from 'node:fs';
import { join } from 'node:path';
import { randomUUID } from 'node:crypto';

import { ProfileService } from './profile.service';
import { UpdateProfileDto } from './dto/update-profile.dto';
import { JwtAuthGuard } from '../auth-service/jwt-auth.guard';

const profileUploadDirectory =
    process.env.PROFILE_UPLOAD_DIR || join(process.cwd(), 'uploads', 'profiles');
mkdirSync(profileUploadDirectory, { recursive: true });

@Controller('profile')
export class ProfileController {
    constructor(
        private readonly profileService: ProfileService,
    ) {}

    @Get('me')
    @UseGuards(JwtAuthGuard)
    getMyProfile(@Req() req: any) {
        return this.profileService.getPrivateProfile(
            Number(req.user.sub),
        );
    }

    @Patch('me')
    @UseGuards(JwtAuthGuard)
    updateMyProfile(
        @Req() req: any,
        @Body() data: UpdateProfileDto,
    ) {
        return this.profileService.updateProfile(
            Number(req.user.sub),
            data,
        );
    }

    @Patch('me/avatar')
    @UseGuards(JwtAuthGuard)
    @UseInterceptors(FileInterceptor('file', {
        storage: diskStorage({
            destination: profileUploadDirectory,
            filename: (_request, file, callback) => {
                const extension = file.originalname.includes('.')
                    ? file.originalname.substring(file.originalname.lastIndexOf('.')).toLowerCase()
                    : '';
                callback(null, `${randomUUID()}${extension}`);
            },
        }),
        limits: { fileSize: 5 * 1024 * 1024 },
        fileFilter: (_request, file, callback) => {
            callback(null, /^image\/(jpeg|png|webp|gif)$/.test(file.mimetype));
        },
    }))
    uploadAvatar(
        @Req() req: any,
        @UploadedFile(new ParseFilePipe({
            validators: [
                new MaxFileSizeValidator({ maxSize: 5 * 1024 * 1024 }),
                new FileTypeValidator({
                    fileType: /^image\/(jpeg|png|webp|gif)$/,
                    skipMagicNumbersValidation: true,
                }),
            ],
        })) file: Express.Multer.File,
    ) {
        return this.profileService.updateAvatar(Number(req.user.sub), file.filename);
    }

    @Get('avatar/:filename')
    getAvatar(
        @Param('filename') filename: string,
        @Res() response: Response,
    ) {
        if (!/^[a-zA-Z0-9-]+\.(jpg|jpeg|png|webp|gif)$/.test(filename)) {
            return response.status(404).send();
        }

        return response.sendFile(filename, { root: profileUploadDirectory });
    }

    @Get(':id')
    getProfile(
        @Param('id', ParseIntPipe) userId: number,
    ) {
        return this.profileService.getPublicProfile(userId);
    }
}