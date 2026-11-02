import i18n from "i18next";
import { initReactI18next } from "react-i18next";

import enLang from './locales/en.json';
import frLang from './locales/fr.json';
import esLang from './locales/es.json';

const resources = {
  en: { translation: enLang },
  fr: { translation: frLang },
  es: { translation: esLang },
};

i18n
  .use(initReactI18next)
  .init({
    resources,
	fallbackLng: "fr",
    lng: "en",

    interpolation: {
      escapeValue: false
    }
  });

  export default i18n;