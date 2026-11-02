/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  GameBoard.tsx                                          ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/24 11:00:06 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/09/24 18:28:48 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

import { useEffect, useRef, useState } from 'react';
import Phaser from 'phaser';
import { createGameConfig } from './createGameConfig';
import { themeManager } from './theme/themeManager';
import type { ThemeName } from './config/themeConfig';
import { THEME_NAMES } from './config/themeConfig';

import neonBg from './assets/map/neon/bbm_bg.png';
import steampunkBg from './assets/map/steampunk/bbm_bg.png';
import neonIcon from './assets/icons/bbm_neon_icon.png';
import steampunkIcon from './assets/icons/bbm_steampunk_icon.png';
import type { GameEndedPayload } from "@/services/gameSocketService"

const THEME_BG_ASSETS: Record<ThemeName, string> = {
	neon: neonBg,
	steampunk: steampunkBg,
};

const THEME_ICON_ASSETS: Record<ThemeName, string> = {
	neon: neonIcon,
	steampunk: steampunkIcon,
};

const THEME_LABELS: Record<ThemeName, string> = {
	neon: 'Neon',
	steampunk: 'Steampunk',
};

type GameBoardProps = {onGameEnded: (
	winnerId: number | null,
	winnerName: string | null,
	data: GameEndedPayload) => void}

const GameBoard = ({ onGameEnded }: GameBoardProps) => {
	const containerRef = useRef<HTMLDivElement | null>(null);
	const gameRef = useRef<Phaser.Game | null>(null);
	const [activeTheme, setActiveTheme] = useState<ThemeName>(themeManager.getTheme());

	useEffect(() => {
		if (gameRef.current || !containerRef.current) return;

		gameRef.current = new Phaser.Game(createGameConfig(containerRef.current, onGameEnded));

		return () => {
			gameRef.current?.destroy(true);
			gameRef.current = null;
		};
	}, [onGameEnded]);

	useEffect(() => {
		const removeListener = themeManager.addThemeChangeListener(setActiveTheme);
		return removeListener;
	}, []);

	return (
		<div
			className="relative w-full h-full overflow-hidden rounded-2xl"
			style={{
				backgroundImage: `url(${THEME_BG_ASSETS[activeTheme]})`,
				backgroundSize: 'cover',
				backgroundPosition: 'center',
				backgroundRepeat: 'no-repeat',
				containerType: 'size',
			}}
		>
			<div ref={containerRef} className="absolute inset-0" />

			<div className="absolute inset-0 z-10 pointer-events-none">
				<div
					className="absolute flex flex-col pointer-events-auto"
					style={{
						top: '2.3148cqh',
						right: '1.3021cqw',
						gap: '0.5cqw',
					}}
				>
					{THEME_NAMES.map((theme) => (
						<button
							key={theme}
							onClick={() => themeManager.setTheme(theme)}
							title={THEME_LABELS[theme]}
							style={{
								width: '4.2969cqw',
								height: '4.2969cqw',
							}}
							className={`rounded-lg overflow-hidden border-2 transition-opacity ${
								activeTheme === theme
									? 'border-white opacity-100'
									: 'border-white/30 opacity-60 hover:opacity-90'
							}`}
						>
							<img
								src={THEME_ICON_ASSETS[theme]}
								alt={THEME_LABELS[theme]}
								className="w-full h-full object-cover"
							/>
						</button>
					))}
				</div>
			</div>
		</div>
	);
};

export default GameBoard;
