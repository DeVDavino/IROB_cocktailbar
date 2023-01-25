const char MAIN_PAGE[] PROGMEM = R"=====(
<!DOCTYPE html>
<html >
    <head>
        <title>Cocktail Bar</title>
        <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0">
    </head>
    <style>
        body {
            margin: 0;
            padding: 0; 
            font-size: 14px;
            background: linear-gradient(#e66465, #9198e5);
            font-family: sans-serif;
            height: 100vh;
        }

        header {
            position: absolute; 
            top:0; 
            width: 100%; 
            height: 15vh; 
            background: #140005;
        }

        h1 {
            position: absolute; 
            color: #ffffff; 
            font-size: 270%;
            top: 50%; 
            left: 50%; 
            transform: translate(-50%, -50%); 
            margin: 0;
            width: 100%;
            text-align: center;
        }

        section {
            position: relative;
            width: 80%; 
            margin: auto;
            top: 20vh; 
        }

        h2 {
            color: #140005;
            margin: 0;
        }

        hr {
            height: 5px;
            background: #140005;
            border: none;
        }

        button {
            font-size: 200%;
            width: 100%;
            border: none;
            background: #140005;
            color: #fcfcff;
            border-radius: 10px;
            padding: 1.5vh 0;
            margin: 1vh 0;
            cursor: pointer;
        }
    </style>
    <body>
        <header>
            <h1>COCKTAIL BAR</h1>
        </header>
        <section>
          <h2>Mix</h2>
          <hr/>
          <form action="/water" method="POST">
            <button type="submit">Water</button>
          </form>
          <form action="/vodka-cola" method="POST">
            <button type="submit">Vodka Cola</button>
          </form>
          <form action="/blue-moon" method="POST">
              <button type="submit">Blue Moon</button>
          </form>
          <form action="/chardonnay" method="POST">
              <button type="submit">Chardonnay</button>
          </form>
          <form action="/rose" method="POST">
              <button type="submit">Rosé</button>
          </form>
          <form action="/cola" method="POST">
              <button type="submit">Cola</button>
          </form>
          <form action="/clean" method="POST">
            <button type="submit">Scoonmaken / Legen</button>
        </form>
        </section>
    </body>
</html>
)=====";