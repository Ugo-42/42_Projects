import Card from "../components/ui/Card"

import PublicLayout from "../components/layouts/PublicLayout"

import { useNavigate } from "react-router-dom"
import { useTranslation } from "react-i18next"

function PrivacyPage() {

	const { t } = useTranslation()
	const navigate = useNavigate()

	return (
		<PublicLayout>
			<Card
				titleKey={t("terms.privacy_policy")}
				isOpen={true}
				onClose={() => navigate(-1)}
			>
				<div className="max-h-[60vh] max-w-full scrollbar-thin scrollbar-thumb-info scrollbar-track-transparent overflow-y-auto space-y-6 text-white px-2">

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.privacy.gathering.title")}
						</h3>
						<p>
								{t("terms.privacy.gathering.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.privacy.info_use.title")}
						</h3>
						<p>
							{t("terms.privacy.info_use.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.privacy.storage.title")}
						</h3>
						<p>
							{t("terms.privacy.storage.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.privacy.third_party.title")}
						</h3>
						<p>
							{t("terms.privacy.third_party.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.privacy.cookies_local_storage.title")}
						</h3>
						<p>
							{t("terms.privacy.cookies_local_storage.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.privacy.security.title")}
						</h3>
						<p>
							{t("terms.privacy.security.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.privacy.rights.title")}
						</h3>
						<p>
							{t("terms.privacy.rights.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.privacy.project_nature.title")}
						</h3>
						<p>
							{t("terms.privacy.project_nature.content")}
						</p>
					</section>

					<div className="border-t border-info pt-4 text-center text-sm text-white/60">
						<p>{t("terms.lastly_updated")}</p>
						<p>Bomberman • 42 School Project</p>
					</div>

				</div>
			</Card>
		</PublicLayout>
	)
}

export default PrivacyPage