#ifndef IMPERTINENT_HPP
#define IMPERTINENT_HPP

namespace JuNOCpp
{
    class Impertinent
    {
    protected:
        bool impertinent;
    public:
        Impertinent(): impertinent(false) {}
        virtual ~Impertinent() =  default;

        bool isImpertinent() { return impertinent; }
        virtual void makeImpertinent() = 0;
        virtual void activate() = 0;
        virtual void deactivate() = 0;
    };
}
#endif // !IMPERTINENT_HPP