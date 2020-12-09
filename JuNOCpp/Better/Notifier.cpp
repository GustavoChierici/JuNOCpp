#include "Notifier.hpp"
#include "BetterPremise.hpp"

namespace JuNOCpp
{
    void Notifier::insert(std::shared_ptr<Notifiable>&& notifiable)
    {
        // this->notifiables.insertInfo(&notifiable);
        notfs.insert(notfs.end(), notifiable);
    }

    void Notifier::notify(const bool renotify /* = false */)
    {
        // auto aux = this->notifiables.getFirst();

        // if(this->notifiables.counter > 0)
        //     while(aux)
        //     {
        //         auto a = aux->getInfo()->get();
        //         std::cout << a << std::endl;
        //         aux = aux->getNext();
        //     }

        for(auto notf : notfs)
        {
            // std::cout << notf.lock().get() << std::endl ;
            notf->update(renotify);
        }
    }
}