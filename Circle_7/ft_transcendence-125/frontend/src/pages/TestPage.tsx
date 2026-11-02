import Card from '@/components/ui/Card'
import Button from '@/components/ui/Button'
import Avatar from '@/components/ui/Avatar'
import Badge from '@/components/ui/Badge'
import Spinner from '@/components/ui/Spinner'
import Input from '@/components/ui/Input'
import Toast from '@/components/ui/Toast'
import Modal from '@/components/ui/Modal'
import Dropdown from '@/components/ui/Dropdown'
import { useState } from 'react'
import { useTranslation } from 'react-i18next'


function TestPage() {

    const { t, i18n } = useTranslation()

    const [email, setEmail] = useState('')
    const [password, setPassword] = useState('')
    const [loading, setLoading] = useState(false)
    const [showToast, setShowToast] = useState(false)
    const [showModal, setShowModal] = useState(false)
    const [showCard, setShowCard] = useState(true)
    const [selectedOption, setSelectedOption] = useState('EN')

    const languageOptions = [
      { labelKey: "dropdown.en", onClick: () => {setSelectedOption('EN'); i18n.changeLanguage('en')} },
      { labelKey: "dropdown.fr", onClick: () => {setSelectedOption('FR'); i18n.changeLanguage('fr')} },
      { labelKey: "dropdown.es", onClick: () => {setSelectedOption('ES'); i18n.changeLanguage('es')} },
    ]

    const handleLoadClick = () => {
        setLoading(true)
        setTimeout(() => {
            setLoading(false)
        }, 2000)
    }

  return (
    <div className="mx-auto p-8 flex flex-col items-center gap-4 ">
      <Card
        isOpen={showCard}
        onClose={() => setShowCard(false)}
        titleKey="nav.profile"
        footer={ <Button type="button" variant="info" onClick={handleLoadClick} disabled={loading} >
      {loading ? <Spinner size="sm" variant="light" /> : t('button.submit')}
    </Button>}>
        <div className="flex flex-col items-center  gap-4">
            <div className="relative inline-block">
                <Avatar pseudo="mimi" src="" size="lg" />
                <Badge labelKey="status.offline" variant="error" className="absolute top-1 -right-1" />
            </div>


            <div className="md:flex md:flex-col md:gap-2">
                <p className="font-micro-5 text-info text-5xl text-center uppercase">Mimi</p>
                <Input labelKey="Email" placeHolderKey="enter_email" type="email" value={email} onChange={(e) => setEmail(e.target.value)} />
                <Input labelKey="password" placeHolderKey="enter_password" type="password" value={password} onChange={(e) => setPassword(e.target.value)} />
            </div>
        </div>
      </Card>
      <Button onClick={() => setShowToast(true)} variant="success">{t('button.submit')}</Button>
      {showToast && (
        <Toast
            labelKey="toast.profile.updated.success"
            variant="success"
            onClose={() => setShowToast(false)}
        />
      )}


      <Button onClick={() => setShowModal(true)}>{t('button.submit')}</Button>
      <Modal
        isOpen={showModal}
        onClose={() => setShowModal(false)}
        footer={
            <>
                <Button variant='primary' onClick={() => setShowModal(false)}>{t('button.confirm')}</Button>
                <Button variant='secondary' onClick={() => setShowModal(false)}>{t('button.cancel')}</Button>
            </>
        }
      >
        <p className="text-center">Sending friend request</p>
      </Modal>

      {/* <Nav items={navItems} /> */}
      <Dropdown
        options={languageOptions}
        selectedKey={selectedOption}
        variant='info'
      />
    </div>
  )
}


export default TestPage