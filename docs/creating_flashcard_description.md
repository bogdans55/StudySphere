Opis slučaja upotrebe "Kreiranje jedne kartice":

    Kratak opis:
        Korisnik kreira kartice unosom pitanja, odgovora i odabira težine. Aplikacija kreira karticu i dodaje je u odabrani špil.

    Akteri:
        Korisnik - želi da kreira karticu sa pitanjem, odgovorom i odabranom težinom.

    Preduslovi:
        Aplikacija je pokrenuta i prikazuje se početni ekran.

    Postuslovi:
        Nova kartica je kreirana i dodana u odabrani špil.

    Osnovni tok:
        1. Korisnik unosi tekst pitanja u polje "Pitanje" u aplikaciji.
        2. Korisnik unosi tekst odgovora u polje "Odgovor" u aplikaciji.
        3. Korisnik odabira težinu pitanja putem radio dugmića (lako, srednje, teško).
        4. Korisnik pritisne dugme za kreiranje kartice.
        5. Aplikacija kreira karticu sa unetim podacima (pitanje, odgovor, težina).
        6. Aplikacija dodaje kreiranu karticu u odabrani špil.
        7. Aplikacija očisti polja za unos pitanja i odgovora.

    Alternativni tokovi:
        - A1: Neočekivani izlaz iz aplikacije. Ukoliko u bilo kojem koraku korisnik isključi aplikaciju, kartica neće biti kreirana i slučaj upotrebe se prekida.
        - A2: Nepopunjena sva polja za unos. Ukoliko korisnik pokuša kreirati karticu bez unosa pitanja, odgovora ili odabrane težine, aplikacija prikazuje poruku o grešci.

    Podtokovi:
        /

    Specijalni zahtevi:
        /

    Dodatne informacije:
        /
