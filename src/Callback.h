#define     CC_CALLBACK_0(__selector__, __target__,...)   std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define     CC_CALLBACK_1(__selector__, __target__,...)   std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define     CC_CALLBACK_2(__selector__, __target__,...)   std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define     CC_CALLBACK_3(__selector__, __target__,...)   std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)
