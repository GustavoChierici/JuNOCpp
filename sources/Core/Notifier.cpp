#include "Notifier.hpp"

namespace JuNOCpp
{
    namespace Core
    {
        /**
         * Insere um Notifiable na ED de notificações
         * 
         * @param notifiable 
         */
        void Notifier::insert(shared_ptr<Notifiable>& notifiable)
        {
            // this->notifiables.insertInfo(notifiable);
            notifiables.push_back(notifiable);
            // notifiables.insert(notifiables.end(), notifiable);
        }

        /**
         * Remove um Notifiable da ED de notificações
         * 
         * @param notifiable 
         */
        void Notifier::remove(shared_ptr<Notifiable>& notifiable)
        {
            // this->notifiables.removeInfo(notifiable);
            notifiables.remove(notifiable);
        }
        /**
         * Insere um Notifiable na ED de notificações
         * 
         * @param notifiable 
         */
        void Notifier::insert(shared_ptr<Notifiable>&& notifiable)
        {
            // this->notifiables.insertInfo(notifiable);
            notifiables.push_back(notifiable);
            // notifiables.insert(notifiables.end(), notifiable);
        }

        /**
         * Remove um Notifiable da ED de notificações
         * 
         * @param notifiable 
         */
        void Notifier::remove(shared_ptr<Notifiable>&& notifiable)
        {
            // this->notifiables.removeInfo(notifiable);
            notifiables.remove(notifiable);
        }

        /**
         * Notifica os Notifiables ligados ao Notifier
         * 
         */
        void Notifier::notify(const bool renotify /* = false */)
        {
            #ifdef FASTER_DATA_STRUCTURES
                for(auto notifiable = notifiables.first; notifiable; notifiable = notifiable->next)
                {
                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().writeNotification(notifiable->element->name, notifiable->element.get());

                        Utils::NOPLogger::Get().incrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                    
                    notifiable->element->update(renotify);

                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().decrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                }
            #elif defined(USE_RANGED_FOR)
                for(auto notifiable : notifiables)
                {
                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().writeNotification(notifiable->name, notifiable.get());

                        Utils::NOPLogger::Get().incrementIdentation();
                    #endif // SHOW_NOP_LOGGER

                    notifiable->update(renotify);

                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().decrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                }
            #else
                for(auto notifiable = notifiables.getFirst(); notifiable; notifiable = notifiable->next)
                {
                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().writeNotification(notifiable->element->name, notifiable->element.get());

                        Utils::NOPLogger::Get().incrementIdentation();
                    #endif // SHOW_NOP_LOGGER

                    notifiable->element->update(renotify);

                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().decrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                }
            #endif // FASTER_DATA_STRUCTURES
        }

        /**
         * Notifica os Notiables ligados ao Notifier que dependem de booleano para serem atualizados
         * 
         * @param renotify 
         * @param status 
         */
        void Notifier::notify(const bool renotify, const bool status)
        {
            #ifdef FASTER_DATA_STRUCTURES
                for(auto notifiable = notifiables.first; notifiable; notifiable = notifiable->next)
                {
                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().writeNotification(notifiable->element->name, notifiable->element.get(), status);

                        Utils::NOPLogger::Get().incrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                    
                    notifiable->element->update(renotify, status);

                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().decrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                }
            #elif defined(USE_RANGED_FOR)
                for(auto notifiable : notifiables)
                {
                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().writeNotification(notifiable->name, notifiable.get(), status);

                        Utils::NOPLogger::Get().incrementIdentation();
                    #endif // SHOW_NOP_LOGGER

                    notifiable->update(renotify, status);

                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().decrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                }
            #else
                for(auto notifiable = notifiables.getFirst(); notifiable; notifiable = notifiable->next)
                {
                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().writeNotification(notifiable->element->name, notifiable->element.get(), status);

                        Utils::NOPLogger::Get().incrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                    
                    notifiable->element->update(renotify, status);

                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().decrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                }
            #endif // FASTER_DATA_STRUCTURES
        }
    } // namespace Core
} // namespace JuNOCpp