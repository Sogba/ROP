#let thesis = (
  name: "Vicevláknové provádění programu",
  major: "Informační technologie",
  class: "ITB4",
  year: 2025,
  author: "Přemek Palát",
  abstract-cs: par([
    Tvorba maturitní práce je jedním z velmi klíčových momentů při studiu. Kvalita zpracování její formální části je pak jedním z nejdůležitějších kritérií při jejím hodnocení. Cíl této práce je popsat jednotlivé kroky během tohoto procesu, doporučit postupy a vytvořit šablonu, která usnadní celý proces.@ujc-tecka
  ]),
  abstract-en: par([
    Abstract in english
  ]),
  keywords-cs: par([
    maturitní práce, šablona
  ]),
  keywords-en: par([
    graduation thesis, template
  ]),
  acknowledgements: par([
    Poděkování
  ]),
  assignment: par([
    Zadání maturitní práce je přílohou této práce.
  ]),
)

= Úvod

// Úvod zde

#pagebreak()

#set heading(numbering: "1.1")

= Nadpis 1

#figure(
  [
    ```tsx
    import type React from "react";

    export default async function Page() {
      return <div>Hello, world!</div>;
    }
    ```
  ],
  supplement: "Výpis",
  caption: "Ukázka kódu v jazyce TypeScript s využitím knihovny React.",
)

#figure(
  table(
    columns: 4,
    [t], [1], [2], [3],
    [y], [0.3s], [0.4s], [0.8s],
  ),
  caption: [Časy],
)

#figure(
  image("res/logo.svg", width: 50%),
  caption: "Logo školy",
)

#figure(
  $x_(1,2) = frac(-b plus.minus sqrt(b^2 - 4 a c), 2a)$,
  kind: "equation",
  supplement: "Rovnice",
  caption: "Vzorec pro výpočet kvadratické rovnice",
)

== Nadpis 2
=== Nadpis 3
=== Nadpis 3

// Zbytek práce zde
