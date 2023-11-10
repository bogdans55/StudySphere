Opis slučaja upotrebe "kreiranje špila kartica":

    Kratak opis: 
        Korisnik kreira novi špil, zatim kreira kartice, jednu po jednu, i dodaje ih u špil. Aplikacija na kraju sačuva špil na serveru. 

    Akteri:
        Korisnik - želi da kreira špil kartica

    Preduslovi: 
        Aplikacija je pokrenuta i prikazuje se početni ekran.

    Postuslovi:
        Špil je kreiran i sačuvan na serveru.

    Osnovni tok:
        1. Korisnik pritiska dugme "Kreiraj novi špil" sa početnog ekrana. 
        2. Aplikacija prikazuje ekran za kreiranje novog špila.
        3. Korisnik unosi naziv špila.
        4. Korisnik bira da li će špil biti javan ili privatni.
        5. Sve dok korisnik ne klikne dugme "Završi dodavanje":
            5.1. Prelazi se na slučaj upotrebe "kreiranje jedne kartice". Po završetku, vraća se na korak 5.
        6. Aplikacija prikazuje kreirane kartice.
        7. Ako korisnik želi da napravi još kartica, klikne dugme "Dodaj karticu".
            7.1. Prelazi se na korak 5.
        8. Ako korisnik pritisne dugme "Otkaži".
            8.1. Pitati korisnika da li je siguran da želi da otkaže kreiranje špila.
                8.1.1. Ako korisnik odgovori potvrdno, prelazi se na korak 11.
                8.1.2. Ako korisnik odgovori negativno, prelazi se na korak 6.
        9. Korisnik pritiska dugme "Sačuvaj špil".
        10. Prelazi se na slučaj upotrebe "Čuvanje kreiranog špila". Po završetku, prelazi se na korak 10.
        11. Aplikacija prikazuje početni ekran.
        
    Alternativni tokovi:
        - A1: Neočekivani izlaz iz aplikacije. Ukoliko u bilo kojem koraku korisnik isključi aplikaciju, sve eventualno zapamćene informacije o trenutnom špilu se poništavaju i aplikacija završava rad. Slučaj upotrebe se završava.
        
    Podtokovi: /

    Specijalni zahtevi:
        Aplikacija je povezana na internet kako bi se špil sačuvao na serveru.

    Dodatne informacije: /
