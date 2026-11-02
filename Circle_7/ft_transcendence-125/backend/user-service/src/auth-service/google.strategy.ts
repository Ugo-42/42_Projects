import { Injectable, Logger, UnauthorizedException } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { Profile, Strategy } from 'passport-google-oauth20';

@Injectable()
export class GoogleStrategy extends PassportStrategy(Strategy, 'google') {
    private readonly logger = new Logger(GoogleStrategy.name);
    private readonly googleOAuthEnabled: boolean;

    constructor() {
        const clientID = process.env.GOOGLE_CLIENT_ID?.trim();
        const clientSecret = process.env.GOOGLE_CLIENT_SECRET?.trim();
        const callbackURL = process.env.GOOGLE_CALLBACK_URL?.trim();
        const enabled = Boolean(clientID && clientSecret && callbackURL);

        super({
            // Keep service bootable when OAuth env vars are absent in local/dev.
            clientID: clientID ?? 'google-oauth-disabled',
            clientSecret: clientSecret ?? 'google-oauth-disabled',
            callbackURL: callbackURL ?? 'http://localhost:3000/auth/google/callback',
            scope: ['email', 'profile'],
        });

        this.googleOAuthEnabled = enabled;
        if (!enabled) {
            this.logger.warn('Google OAuth is disabled: missing GOOGLE_CLIENT_ID/GOOGLE_CLIENT_SECRET/GOOGLE_CALLBACK_URL');
        }
    }

    async validate(accessToken: string, refreshToken: string, profile: Profile) {
        if (!this.googleOAuthEnabled) {
            throw new UnauthorizedException('Google OAuth is not configured');
        }

        return {
            provider: 'google',
            providerId: profile.id,
            email: profile.emails?.[0]?.value,
            firstname: profile.name?.givenName,
            lastname: profile.name?.familyName,
            avatar: profile.photos?.[0]?.value,
        };
    }
}