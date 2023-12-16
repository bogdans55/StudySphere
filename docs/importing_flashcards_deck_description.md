Opis slučaja upotrebe "Uvoz špila kartica":

    Kratak opis: 
        Korisnik sa svog računara bira špilove koje želi da uveze u biblioteku. Aplikacija dohvata podatke o špilovima i kreira ih u biblioteci.

    Akteri:
        Korisnik - želi da uveze špilove kartica u neki od podržanih formata.

    Preduslovi: 
        Aplikacija je pokrenuta i prikazuje se početni ekran.

    Postuslovi:
        Izabrani špilovi su uvezeni u biblioteku.

    Osnovni tok:
        1. Korisnik bira opciju za uvoz špilova iz menija.
        2. Aplikacija prikazuje ekran za izbor fajlova.
        3. Korisnik bira fajlove koje želi da uveze.
        4. Aplikacija učitava podatke o špilovima iz fajlova i kreira ih u biblioteci.
        5. Aplikacija prikazuje poruku o uspešnom uvozu špilova.
        6. Aplikacija prikazuje početni ekran.
                
    Alternativni tokovi:
        - A1: Neočekivani izlaz iz aplikacije. Ukoliko u bilo kojem koraku korisnik isključi aplikaciju, špil neće biti uvezen i slučaj upotrebe se prekida.
        - A2: Pokušaj uvoza fajla pogrešnog formata. Ukoliko korisnik pokuša da uveze fajl koji nije u podržanom formatu, aplikacija će prikazati poruku o grešci i slučaj upotrebe se prekida.
        
    Podtokovi: 
        /

    Specijalni zahtevi:
        Aplikacija je povezana na internet kako bi se uvezeni špilovi sačuvali na serveru.

    Dodatne informacije: 
        /
