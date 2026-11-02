import Card from "../components/ui/Card"

import PublicLayout from "../components/layouts/PublicLayout"

import { useNavigate } from "react-router-dom"
import { useTranslation } from "react-i18next"

function TermsPage() {
	
	const { t } = useTranslation()
	const navigate = useNavigate()

	return (
		<PublicLayout>
			<Card
				titleKey="terms.terms_of_service"
				isOpen={true}
				onClose={() => navigate(-1)}
			>
				<div className="max-h-[60vh] max-w-full scrollbar-thin scrollbar-thumb-info scrollbar-track-transparent overflow-y-auto space-y-6 text-white px-2">

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.service.acceptance.title")}
						</h3>
						<p>
							{t("terms.service.acceptance.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.service.account.title")}
						</h3>
						<p>
							{t("terms.service.account.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.service.fairplay.title")}
						</h3>
						<p>
							{t("terms.service.fairplay.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.service.availability.title")}
						</h3>
						<p>
							{t("terms.service.availability.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.service.intellectual_property.title")}
						</h3>
						<p>
							{t("terms.service.intellectual_property.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.service.privacy.title")}
						</h3>
						<p>
							{t("terms.service.privacy.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.service.changes.title")}
						</h3>
						<p>
							{t("terms.service.changes.content")}
						</p>
					</section>

					<section>
						<h3 className="text-primary text-xl font-micro-5 mb-2">
							{t("terms.service.contact.title")}
						</h3>
						<p>
							{t("terms.service.contact.content")}
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

export default TermsPage