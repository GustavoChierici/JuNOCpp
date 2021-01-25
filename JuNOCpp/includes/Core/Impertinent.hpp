#ifndef JUNOCPP_IMPERTINENT_HPP
#define JUNOCPP_IMPERTINENT_HPP

namespace JuNOCpp
{
    namespace Core
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
    } // namespace Core

}
#endif // !JUNOCPP_IMPERTINENT_HPP