Opis slučaja upotrebe "Izvoz špila kartica":

    Kratak opis: 
        Korisnik iz biblioteke špilova bira one koje želi da izveze i na kojoj lokaciji želi da ih sačuva. Aplikacija dohvata podatke o špilovima i kreira fajlove u željenom formatu. 

    Akteri:
        Korisnik - želi da izveze špilove kartica u neki od podržanih formata.

    Preduslovi: 
        Aplikacija je pokrenuta i prikazuje se početni ekran, i biblioteka špilova nije prazna.

    Postuslovi:
        Kreirani je fajl sa podacima o špilu.

    Osnovni tok:
        1. Korisnik bira špilove iz biblioteke sa početnog ekrana i pritiska dumge "Izvezi".
        2. Aplikacija prikazuje ekran za izvoz špilova.
        3. Korisnik bira format i lokaciju na kojoj želi da izveze špilove.
        4. Aplikacija kreira fajlove sa podacima o špilovima u željenom formatu i čuva ih na željenoj lokaciji.
        5. Aplikacija prikazuje poruku o uspešnom izvozu špilova.
        6. Aplikacija prikazuje početni ekran.
                
    Alternativni tokovi:
        - A1: Neočekivani izlaz iz aplikacije. Ukoliko u bilo kojem koraku korisnik isključi aplikaciju, fajl neće biti kreiran i slučaj upotrebe se prekida.
        - A2: Pokušaj čuvanja na lošoj lokaciji. Ukoliko korisnik nema pristup folderu u koji je pokušao da sačuva fajl, aplikacija će prikazati poruku o grešci i slučaj upotrebe se prekida.
        
    Podtokovi: 
        /

    Specijalni zahtevi:
        Aplikacija je povezana na internet kako bi se pristupilo špilu sa servera.

    Dodatne informacije: 
        /
