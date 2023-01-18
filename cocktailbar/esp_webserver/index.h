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
            background: #2C3333;
            font-family: Arial, Helvetica, sans-serif; 
        }

        header {
            position: absolute; 
            top:0; 
            width: 100%; 
            height: 15vh; 
            background: #395B64;
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
            color: #ffffff;
            margin: 0;
        }

        hr {
            height: 5px;
            background: #ffffff;
            border: none;
        }

        button {
            font-size: 200%;
            width: 100%;
            border: none;
            background: #A5C9CA;
            color: #ffffff;
            border-radius: 10px;
            padding: 1vh 0;
            margin: 1vh 0;
        }
    </style>
    <body>
        <header>
            <h1>COCKTAIL BAR</h1>
        </header>
        <section>
            <h2>Mix</h2>
            <hr/>
            <form action="/baco" method="POST">
                <button type="submit">BACO</button>
            </form>
            <form action="/malibu-cola" method="POST">
                <button type="submit">Malibu Cola</button>
            </form>
            <form action="/rum-fanta" method="POST">
                <button type="submit">Rum Fanta</button>
            </form>
            <form action="/malibu-fanta" method="POST">
                <button type="submit">Malibu Fanta</button>
            </form>
        </section>
    </body>
</html>
)=====";