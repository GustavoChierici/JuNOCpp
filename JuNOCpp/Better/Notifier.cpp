#include "Notifier.hpp"

namespace JuNOCpp
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
                // std::cout << notifiable.lock().get() << std::endl ;
                notifiable->element->update(renotify);
            }
        #elif defined(USE_RANGED_FOR)
            for(auto notifiable : notifiables)
                notifiable->update(renotify);
        #else
            for(auto notifiable = notifiables.getFirst(); notifiable; notifiable = notifiable->next)
            {
                // std::cout << notifiable.lock().get() << std::endl ;
                notifiable->element->update(renotify);
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
                // std::cout << notifiable.lock().get() << std::endl ;
                notifiable->element->update(renotify, status);
            }
        #elif defined(USE_RANGED_FOR)
            for(auto notifiable : notifiables)
                notifiable->update(renotify, status);
        #else
            for(auto notifiable = notifiables.getFirst(); notifiable; notifiable = notifiable->next)
            {
                // std::cout << notifiable.lock().get() << std::endl ;
                notifiable->element->update(renotify, status);
            }
        #endif // FASTER_DATA_STRUCTURES
    }
}