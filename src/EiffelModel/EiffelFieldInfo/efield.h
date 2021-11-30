#ifndef EFIELD_H
#define EFIELD_H

#include <string>
#include "../EiffelCore/efeature.h"

class EField : public EFeature {
private:
    std::string _name;

    // ============== OPERATIONS ==============
    // -------- creating --------
public:
    static EField* create(feature_decl_strct* featureDecl);

    bool initSelf();
};

#endif // EFIELD_H
