import Card from "../ui/Card"
import Button from "../ui/Button"
import { useState } from "react"
import { useTranslation } from "react-i18next"

type RulesCardProps = {
	isOpen: boolean
	onClose: () => void
}

function RulesCard({ isOpen, onClose }: RulesCardProps) {

	const { t } = useTranslation()

	const [activeTab, setActiveTab] = useState<"rules" | "controls">("rules")
	

	if (!isOpen)
		return null;
	
	return (
		<div className="fixed inset-0 flex items-center justify-center z-40 overflow-y-auto">
			<Card
				titleKey=""
				isOpen={isOpen}
				onClose={onClose}
				footer={
					<Button
						variant="primary"
						onClick={onClose}
					>
						{t("button.close")}
					</Button>
				}
			>
				<div className="flex flex-col items-center gap-3 max-h-[60vh] scrollbar-thin scrollbar-thumb-info scrollbar-track-transparent overflow-y-auto">
					<div className="flex items-center mt-5 gap-3">
						<Button
							variant={activeTab === "rules" ? "secondary" : "primary"}
							onClick={() => setActiveTab("rules")}>
							{t("nav.rules")}
						</Button>
						<Button
							variant={activeTab === "controls" ? "secondary" : "primary"}
							onClick={() => setActiveTab("controls")}>
							{t("rules.controls.cts")}
						</Button>
					</div>

					<div className="w-full mt-2 space-y-5">
						{activeTab === "rules" && (
							<div className="flex flex-col text-white">
									<div className="m-2">
										<h1 className="flex justify-center m-1 text-info text-[30px] font-micro-5">{t("rules.map.title")}</h1>
										<p className="text-justify"><a className="text-info font-bold">⇢</a> {t("rules.map.text")}</p>
										<p className="test-justify"><a className="text-info font-bold">⇢</a> {t("rules.map.legend")}</p>
									</div>
									<div className="m-2">	
										<h1 className="flex justify-center m-1 text-info text-[30px] font-micro-5">{t("rules.basics.title")}</h1>
										<p className="text-justify"><a className="text-info font-bold">⇢</a> {t("rules.basics.start")}</p>
										<p className="text-justify"><a className="text-info font-bold">⇢</a> {t("rules.basics.bomb")}</p>
										<p className="text-justify"><a className="text-info font-bold">⇢</a> {t("rules.basics.block")}</p>
									</div>
								<div className="flex flex-col justify-center">
									<h1 className="flex justify-center m-1 text-info text-[30px] font-micro-5">{t("rules.power_ups.title")}</h1>
									<p className="text-left"><a className="text-info font-bold">⇢</a> {t("rules.power_ups.bomb_plus")}</p>
									<p className="text-left"><a className="text-info font-bold">⇢</a> {t("rules.power_ups.bomb_minus")}</p>
									<p className="text-left"><a className="text-info font-bold">⇢</a> {t("rules.power_ups.kick")}</p>
									<p className="text-left"><a className="text-info font-bold">⇢</a> {t("rules.power_ups.speed_plus")}</p>
									<p className="text-left"><a className="text-info font-bold">⇢</a> {t("rules.power_ups.speed_minus")}</p>
									<p className="text-left"><a className="text-info font-bold">⇢</a> {t("rules.power_ups.flame_plus")}</p>
									<p className="text-left"><a className="text-info font-bold">⇢</a> {t("rules.power_ups.flame_minus")}</p>
								</div>
							</div>
						)}

						{activeTab === "controls" && (
							<div className="flex flex-col text-white">
									<div className="m-2">
										<h1 className="flex justify-center m-1 text-info text-[30px] font-micro-5">{t("rules.controls.solo")}</h1>	
										<p className="flex justify-center m-2">
											<kbd>W</kbd>
										</p>
										<p className="flex justify-center gap-2">
											<kbd>A</kbd><kbd>S</kbd><kbd>D</kbd>
										</p>
										<p className="flex justify-center m-2">
											<kbd>SPACE</kbd>
										</p>
									</div>
									<div className="m-2">	
										<p><a className="text-info font-bold">⇢</a> {t("rules.controls.W")}</p>
										<p><a className="text-info font-bold">⇢</a> {t("rules.controls.A")}</p>
										<p><a className="text-info font-bold">⇢</a> {t("rules.controls.S")}</p>
										<p><a className="text-info font-bold">⇢</a> {t("rules.controls.D")}</p>
										<p><a className="text-info font-bold">⇢</a> {t("rules.controls.space")}</p>
									</div>
								<div className="m-2">
									<h1 className="flex justify-center m-1 text-info text-[30px] font-micro-5">{t("rules.controls.p_2")}</h1>	
									<p className="flex justify-center m-2">
										<kbd>↑</kbd>
									</p>
									<p className="flex justify-center gap-2">
										<kbd>←</kbd><kbd>↓</kbd><kbd>→</kbd>
									</p>
									<p className="flex justify-end m-2">
										<kbd>0</kbd>
									</p>
								</div>
								<div className="m-2">	
									<p><a className="text-info font-bold">⇢</a> {t("rules.controls.up")}</p>
									<p><a className="text-info font-bold">⇢</a> {t("rules.controls.left")}</p>
									<p><a className="text-info font-bold">⇢</a> {t("rules.controls.down")}</p>
									<p><a className="text-info font-bold">⇢</a> {t("rules.controls.right")}</p>
									<p><a className="text-info font-bold">⇢</a> {t("rules.controls.bomb")}</p>
								</div>
							</div>
						)}
					</div>
				</div>
			</Card>
		</div>
	)
}

export default RulesCard