Opis slučaja upotrebe "Korišćenje špila kartica":

    Kratak opis: 
        Korisnik bira špil iz biblioteke na početnom ekranu. Aplikacija učitavanja podešavanja. Korisniku prikazuje karticu po karticu koja sadrži pitanje. Kada se odluči za to, korisnik može da vidi odgovor. Zatim treba da oceni svoje znanje za dato pitanje jednom od ponudjenjih opcija. Kada prodje kroz sve date kartice, aplikacija pamti informacije o korisnikovom nivou znanja.  

    Akteri:
        Korisnik - koristi špil za učenje

    Preduslovi: 
        Aplikacija je pokrenuta i prikazuje se početni ekran, i biblioteka špilova nije prazna.

    Postuslovi:
        Aplikacija je sačuvala informacije o korisnikovom nivou znanja.

    Osnovni tok:
        1. Korisnik bira špil iz biblioteke sa početnog ekrana.
        2. Aplikacija učitava podešavanja za špilove.
        3. Aplikacija na osnovu pametnog algoritma pravi izbor odabranog broja kartica iz špila.
        4. Sve dok ne prikaže sve izabrane kartice:
            4.1. Aplikacija prikazuje karticu sa pitanjem.
            4.2. Korisnik klikom na dugme otkriva odgovor.
            4.3. Korisnik ocenjuje svoje znanje za dato pitanje.
        5. Aplikacija čuva informacije o korisnikovom nivou znanja za izabrana pitanja.
        6. Aplikacija prikazuje početni ekran.
        
    Alternativni tokovi:
        - A1: Neočekivani izlaz iz aplikacije. Ukoliko u bilo kojem koraku korisnik isključi aplikaciju, sve eventualno zapamćene informacije o trenutnom špilu se poništavaju i aplikacija završava rad. Slučaj upotrebe se završava.
        
    Podtokovi: 
        /

    Specijalni zahtevi:
        Aplikacija je povezana na internet kako bi se pristupilo špilu sa servera.

    Dodatne informacije: 
        Korisnik može da klikom na dugme okreće karticu sa pitanjem i odgovorom.
        Tokom korišćenja špila, aplikacija pamti informacije o korisnikovom nivou znanja za svako pitanje.
