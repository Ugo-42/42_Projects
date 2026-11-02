import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import { BrowserRouter } from 'react-router-dom'
import './index.css'
import './utils/i18n'
import App from './App.tsx'
import { AuthProvider } from './contexts/AuthContext.tsx'
import { ChatProvider } from "@/contexts/ChatContext"
import { PresenceProvider } from './contexts/PresenceContext.tsx'

createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <BrowserRouter>
      <AuthProvider>
        <PresenceProvider>
          <ChatProvider>
            <App />
          </ChatProvider>
        </PresenceProvider>
      </AuthProvider>
    </BrowserRouter>
  </StrictMode>,
)
