#ifndef CONFIG_HPP
#define CONFIG_HPP

/**
 * @brief (EXPERIMENTAL) Constante que determina se o JuNOC++ usará
 * smart pointers customizados criados para o JuNOC++ (mais rápidos,
 * mas menos estáveis) ou se usará os smart pointers da STL (mais
 * lentos, mas mais estáveis)
 * 
 * Default: undefined
 * 
 */
// #define USE_CUSTOM_SMART_PTRS

/**
 * @brief Constante que determina se o JuNOC++ utilizará suas EDs de
 * notificação com acesso público para tornar o processo de notificação
 * mais rápido 
 * 
 * *Obs: esta configuração só vale para containers do próprio JuNOC++, 
 * desabilite se você utilizar algum outro
 * *Obs²: esta configuração é incompatível com a configuração
 * USE_RANGED_FOR, utilize apenas uma delas para evitar comportamento
 * indefinido
 * 
 * Default: defined
 * 
 */
#define FASTER_DATA_STRUCTURES

/**
 * @brief Constante que determina se o JuNOC++ utilizará Ranged Fors
 * para percorrer suas EDs de notificação. Para utilizar um container
 * que não seja um dos próprios do JuNOC++ com essa configuração, ele
 * precisa suportar iteradores
 *  
 * *Obs: esta configuração é incompatível com a configuração 
 * FASTER_DATA_STRUCTURES, utilize apenas uma delas para evitar
 * um comportamento indefinido
 * 
 * Default: undefined
 * 
 */
// #define USE_RANGED_FOR

#endif // !CONFIG_HPP
 