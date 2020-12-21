#include "Notifier.hpp"
#include "BetterPremise.hpp"

namespace JuNOCpp
{
    void Notifier::insert(std::shared_ptr<Notifiable>&& notifiable)
    {
        this->notifiables.insertInfo(notifiable);
        notfs.insert(notfs.end(), notifiable);
    }

    void Notifier::remove(std::shared_ptr<Notifiable>&& notifiable)
    {
        this->notifiables.removeInfo(notifiable);
    }

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