#include "Notifier.hpp"
#include "BetterPremise.hpp"

namespace JuNOCpp
{
    /**
     * Insere um Notifiable na ED de notificações
     * 
     * @param notifiable 
     */
    void Notifier::insert(std::shared_ptr<Notifiable>&& notifiable)
    {
        this->notifiables.insertInfo(notifiable);
        notfs.insert(notfs.end(), notifiable);
    }

    /**
     * Remove um Notifiable da ED de notificações
     * 
     * @param notifiable 
     */
    void Notifier::remove(std::shared_ptr<Notifiable>&& notifiable)
    {
        this->notifiables.removeInfo(notifiable);
    }

    /**
     * Notifica os Notifiables ligados ao Notifier
     * 
     */
    void Notifier::notify(const bool renotify /* = false */)
    {
        auto aux = this->notifiables.getFirst();

        while(aux)
        {
            aux->getInfo()->update(renotify);
            // std::cout << a << std::endl;
            aux = aux->getNext();
        }

        // for(auto notf : notfs)
        // {
        //     // std::cout << notf.lock().get() << std::endl ;
        //     notf->update(renotify);
        // }
    }

    /**
     * Notifica os Notiables ligados ao Notifier que dependem de booleano para serem atualizados
     * 
     * @param renotify 
     * @param status 
     */
    void Notifier::notify(const bool renotify, const bool status)
    {
        auto aux = this->notifiables.getFirst();

        while(aux)
        {
            aux->getInfo()->update(renotify, status);
            // std::cout << a << std::endl;
            aux = aux->getNext();
        }

        // for(auto notf : notfs)
        // {
        //     // std::cout << notf.lock().get() << std::endl ;
        //     notf->update(renotify);
        // }
    }
}