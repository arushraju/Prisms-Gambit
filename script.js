let red_mirror = document.getElementsByClassName('rmirror');
for(let a = 0 ; a< red_mirror.length ; a++)
{
    red_mirror[a].innerHTML = '<img src="./piece_image/Red Mirrror.png" width="97px" height="97px"/>';
}

let red_deflector = document.getElementsByClassName('rdeflector');
for(let a = 0 ; a< red_deflector.length ; a++)
{
    red_deflector[a].innerHTML = '<img src="./piece_image/Red deflector.png" width="97px" height="97px"/>';
}

let red_king = document.getElementsByClassName('rking');
for(let a = 0 ; a< red_king.length ; a++)
{
    red_king[a].innerHTML = '<img src="./piece_image/Red king.png" width="97px" height="97px"/>';
}

let red_blocker = document.getElementsByClassName('rblocker');
for(let a = 0 ; a< red_blocker.length ; a++)
{
    red_blocker[a].innerHTML = '<img src="./piece_image/Red blocker .png" width="97px" height="97px"/>';
}

let red_laser = document.getElementsByClassName('rlaser');
for(let a = 0 ; a< red_laser.length ; a++)
{
    red_laser[a].innerHTML = '<img src="./piece_image/Red laser.png" width="97px" height="97px"/>';
}



let blue_mirror = document.getElementsByClassName('bmirror');
for(let a = 0 ; a< blue_mirror.length ; a++)
{
    blue_mirror[a].innerHTML = '<<img src="./piece_image/Blue Mirror.png" width="97px" height="97px"/>';
}

let blue_deflector = document.getElementsByClassName('bdeflector');
for(let a = 0 ; a< blue_deflector.length ; a++)
{
    blue_deflector[a].innerHTML = '<img src="./piece_image/Blue deflector.png" width="97px" height="97px"/>';
}

let blue_king = document.getElementsByClassName('bking');
for(let a = 0 ; a< blue_king.length ; a++)
{
    blue_king[a].innerHTML = '<img src="./piece_image/Blue king.png" width="97px" height="97px"/>';
}

let blue_blocker = document.getElementsByClassName('bblocker');
for(let a = 0 ; a< blue_blocker.length ; a++)
{
    blue_blocker[a].innerHTML = '<img src="./piece_image/Blue blocker.png" width="97px" height="97px"/>';
}

let blue_laser = document.getElementsByClassName('blaser');
for(let a = 0 ; a< blue_laser.length ; a++)
{
    blue_laser[a].innerHTML = '<img src="./piece_image/Red laser.png" width="97px" height="97px"/>';
}

let rotate = document.getElementsByClassName('rotate90');
for(let a = 0 ;a<rotate.length;a++)
{
    let temp = rotate[a].querySelector('img');
    temp.style.transform = 'rotate(-90deg)';
}
rotate = document.getElementsByClassName('rotate180');
for(let a = 0;a<rotate.length;a++)
{
    let temp = rotate[a].querySelector('img');
    temp.style.transform = 'rotate(180deg)';
}
rotate = document.getElementsByClassName('rotatea90');
for(let a = 0 ;a<rotate.length;a++)
{
    let temp = rotate[a].querySelector('img');
    temp.style.transform = 'rotate(90deg)';
}
