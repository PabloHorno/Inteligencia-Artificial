#ifndef CSP_SELECCION_VARIABLE_H_INCLUDED
#define CSP_SELECCION_VARIABLE_H_INCLUDED


template <typename T>
unsigned Problema_csp<T>::seleccion_variable_estatica()
{
    return(variables_sin_etiquetar.back());
}

template <typename T>
void Problema_csp<T>::bloquea_variable()
{
    variables_sin_etiquetar.pop_back();
}

template <typename T>
void Problema_csp<T>::libera_variable(const unsigned variable)
{
    variables_sin_etiquetar.push_back(variable);
}

#endif // CSP_SELECCION_VARIABLE_ALGORITMO_H_INCLUDED
