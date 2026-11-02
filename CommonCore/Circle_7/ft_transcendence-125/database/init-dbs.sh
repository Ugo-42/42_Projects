#!/bin/bash
set -e

psql -v ON_ERROR_STOP=1 --username "$POSTGRES_USER" --dbname "${POSTGRES_DB:-$POSTGRES_USER}" <<-EOSQL

    DO \$\$
    BEGIN
        IF NOT EXISTS (SELECT FROM pg_catalog.pg_roles WHERE rolname = '${AUTH_DB_USER}') THEN
            CREATE USER "${AUTH_DB_USER}" WITH PASSWORD '${AUTH_DB_PASSWORD}';
        END IF;
        
        IF NOT EXISTS (SELECT FROM pg_catalog.pg_roles WHERE rolname = '${USER_DB_USER}') THEN
            CREATE USER "${USER_DB_USER}" WITH PASSWORD '${USER_DB_PASSWORD}';
        END IF;
        
        IF NOT EXISTS (SELECT FROM pg_catalog.pg_roles WHERE rolname = '${GAME_DB_USER}') THEN
            CREATE USER "${GAME_DB_USER}" WITH PASSWORD '${GAME_DB_PASSWORD}';
        END IF;
    END
    \$\$;

    SELECT 'CREATE DATABASE "${AUTH_DB_NAME}"' 
    WHERE NOT EXISTS (SELECT FROM pg_database WHERE datname = '${AUTH_DB_NAME}')\gexec

    SELECT 'CREATE DATABASE "${USER_DB_NAME}"' 
    WHERE NOT EXISTS (SELECT FROM pg_database WHERE datname = '${USER_DB_NAME}')\gexec

    SELECT 'CREATE DATABASE "${GAME_DB_NAME}"' 
    WHERE NOT EXISTS (SELECT FROM pg_database WHERE datname = '${GAME_DB_NAME}')\gexec

    ALTER DATABASE "${AUTH_DB_NAME}" OWNER TO "${AUTH_DB_USER}";
    ALTER DATABASE "${USER_DB_NAME}" OWNER TO "${USER_DB_USER}";
    ALTER DATABASE "${GAME_DB_NAME}" OWNER TO "${GAME_DB_USER}";

EOSQL
