<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Lily+Script+One&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css2?family=Lusitana:wght@400;700&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="../css/plantPage.css">
    <title>BloomBliss</title>
</head>
<body>
    <header>
        <img src="../img/simpele logo zonder achtergrond.png" class="logo">
        <h1 class="logoName">BloomBliss</h1>
    </header>
    <main>
        <section class="MijnPlanten">
            <h2>Mijn planten</h2>
            <section class="PlantList">
                <section class="card">
                    <img src="../img/pexels-cottonbro-studio-5858235.jpg" alt="foto van een monstera" class="cardImg">
                    <h1>Monstera</h1>
                </section>
                <section class="card">
                    <img src="../img/pexels-cottonbro-studio-5858235.jpg" alt="foto van een monstera" class="cardImg">
                    <h1>pothos</h1>
                </section>
            </section>
        </section>
        <section class="PlantOverview">
            <img src="../img/pexels-cottonbro-studio-5858235.jpg" class="overviewImg">
            <section class="PlantInfo">
                <h2>{{$level->plant_name}}</h2>
                <section class="waterProcent">
                    <h2>the current moisture is:</h2>
                    <h1>{{$measurement->measurement}}%</h1>
                
                <a href="giveWater"><button class="waterButton">Give water</button></a>
                </section>
                <section class="inlineCards">
                    <section class="waterLevel">
                        <h2>Minimum moisture level:</h2>                  
                    
                        <h1 class="showLevel">{{$level->level}}</h1>
                        <section class="levelbuttons">
                            <a href="minLevel"><button>-</button></a>
                            <a href="plusLevel"><button>+</button></a>
                        </section>
                    </section>
                    <section class="waterAuto">
                        <h2>Automation:</h2>
                        <!-- <h1>{{$automation->is_on}}</h1> -->
                        <h1>
                            <?php if($automation->is_on == 1):?>
                                On
                            <?php else : ?>
                                Off
                            <?php endif;?>
                        </h1>
                        <a href="setAutomation"><button>On/Off</button></a>
                    </section>
                </section>
            </section>
        </section>
        
    </main>
    
</body>
</html>