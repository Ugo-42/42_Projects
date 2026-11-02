ALTER TABLE "User"
  DROP COLUMN "twoFactorSecretEncrypted",
  DROP COLUMN "twoFactorTempSecretEncrypted",
  ADD COLUMN "twoFactorCodeHash" TEXT,
  ADD COLUMN "twoFactorCodeExpiresAt" TIMESTAMP(3),
  ADD COLUMN "twoFactorCodePurpose" TEXT;