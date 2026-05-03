using System.Collections.Generic;
using LibrarieModele; 

namespace AdministrareDate
{
    public interface IStocareDate
    {
        void AdaugaClient(Client c);
        List<Client> GetClienti();
        Client CautaClientDupaNume(string nume); 
        bool StergeClientDupaNume(string nume);
        bool UpdateClient(Client clientActualizat);
    }
}