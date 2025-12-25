//Complete setup of the board.
const setup_catalog_container =  document.querySelector('.setup-catalog-container'); 

//Rotate button
document.querySelector('.rotate-button-container').style.display = 'none';

//Complete Chess Board
const chessboard_container = document.querySelector('.board-container');
const chessboard = document.querySelector('.board');

//Instructions of the game
const instruction_container = document.querySelector('.instructions');
let instruction_heading = instruction_container.querySelector('.instruction-heading');
let instruction_content = instruction_container.querySelector('.instruction-content');

//Form 
const form_container = document.querySelector("#form-container");
form_container.style.display = 'none'; //No display for form initially.

const form = document.getElementById('form'); //gettig the data from form
let depth; //Engine depth
let player_color; //Player color

//Back Button
const back_button = document.querySelector('.back-button');



//Uses the class of board and fills or remove the images.
function board_update(){

    const red_mirror_image = './Media/Red_Mirror.png';
    const blue_mirror_image = './Media/Blue_Mirror.png';
    const red_laser_image = './Media/Red_laser.png';
    const blue_laser_image = './Media/Blue_laser.jpeg';
    const red_deflector_image = './Media/Red_deflector.png';
    const blue_deflector_image = './Media/Blue_deflector.png';
    const red_sheild_image = './Media/Red_blocker .png';
    const blue_sheild_image = './Media/Blue_blocker.png';
    const red_king_image = './Media/Red_king.png';
    const blue_king_image = './Media/Blue_king.png';
    //And now We could fill the image on them
    const squares_fill_image = document.getElementsByClassName('square');
    for(let i = 0;i<squares_fill_image.length;i++){
        squares_fill_image[i].innerHTML = '';
        //First create a piece wrapper
        const piece_wrapper_div = document.createElement('div');
        piece_wrapper_div.classList.add('piece-wrapper');
        //Fills the blue mirror
        if(squares_fill_image[i].classList.contains('bmirror')){
            if(squares_fill_image[i].classList.contains('orient3')){
                piece_wrapper_div.innerHTML = `<img src='${blue_mirror_image}'/>`;
            }
            else if(squares_fill_image[i].classList.contains('orient2')){
                piece_wrapper_div.innerHTML = `<img src='${blue_mirror_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(90deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient1')){
                piece_wrapper_div.innerHTML = `<img src='${blue_mirror_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(180deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient4')){
                piece_wrapper_div.innerHTML = `<img src='${blue_mirror_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(270deg)';
            }
        }
        //Fills the red mirror
        else if(squares_fill_image[i].classList.contains('rmirror')){
            if(squares_fill_image[i].classList.contains('orient3')){
                piece_wrapper_div.innerHTML = `<img src='${red_mirror_image}'/>`;
            }
            else if(squares_fill_image[i].classList.contains('orient2')){
                piece_wrapper_div.innerHTML = `<img src='${red_mirror_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(90deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient1')){
                piece_wrapper_div.innerHTML = `<img src='${red_mirror_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(180deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient4')){
                piece_wrapper_div.innerHTML = `<img src='${red_mirror_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(270deg)';
            }
        }
        //Fills the red sheild
        else if(squares_fill_image[i].classList.contains('rsheild')){
            if(squares_fill_image[i].classList.contains('orient1')){
                piece_wrapper_div.innerHTML = `<img src='${red_sheild_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(180deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient2')){
                //console.log('entered into correct image filer')
                piece_wrapper_div.innerHTML = `<img src='${red_sheild_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(90deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient3')){
                piece_wrapper_div.innerHTML = `<img src='${red_sheild_image}'/>`;
            }
            else if(squares_fill_image[i].classList.contains('orient4')){
                piece_wrapper_div.innerHTML = `<img src='${red_sheild_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(270deg)';
            }
        }
        //Fills the blue sheild
        else if(squares_fill_image[i].classList.contains('bsheild')){
            if(squares_fill_image[i].classList.contains('orient1')){
                piece_wrapper_div.innerHTML = `<img src='${blue_sheild_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(180deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient2')){
                piece_wrapper_div.innerHTML = `<img src='${blue_sheild_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(90deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient3')){
                piece_wrapper_div.innerHTML = `<img src='${blue_sheild_image}'/>`;
            }
            else if(squares_fill_image[i].classList.contains('orient4')){
                piece_wrapper_div.innerHTML = `<img src='${blue_sheild_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(270deg)';
            }
        }
        //Fills the red delfector
        else if(squares_fill_image[i].classList.contains('rdeflector')){
            if(squares_fill_image[i].classList.contains('orient1')){
                piece_wrapper_div.innerHTML = `<img src='${red_deflector_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(0deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient2')){
                piece_wrapper_div.innerHTML = `<img src='${red_deflector_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(90deg)';
            }
        }
        //Fills the blue deflector
        else if(squares_fill_image[i].classList.contains('bdeflector')){
            if(squares_fill_image[i].classList.contains('orient1')){
                piece_wrapper_div.innerHTML = `<img src='${blue_deflector_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(0deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient2')){
                piece_wrapper_div.innerHTML = `<img src='${blue_deflector_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(90deg)';
            }
        }
        //Fills the blue king
        else if (squares_fill_image[i].classList.contains('bking')){piece_wrapper_div.innerHTML = `<img src='${blue_king_image}'/>`;}
        //Fills red king
        else if (squares_fill_image[i].classList.contains('rking')){piece_wrapper_div.innerHTML = `<img src='${red_king_image}'/>`;}

        //Fills laser
        else if(squares_fill_image[i].classList.contains('blaser')){
            if(squares_fill_image[i].classList.contains('orient3')){
                piece_wrapper_div.innerHTML = `<img src='${blue_laser_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(0deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient4')){
                piece_wrapper_div.innerHTML = `<img src='${blue_laser_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(-90deg)';
            }
        }
        else if(squares_fill_image[i].classList.contains('rlaser')){
            if(squares_fill_image[i].classList.contains('orient1')){
                piece_wrapper_div.innerHTML = `<img src='${red_laser_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(180deg)';
            }
            else if(squares_fill_image[i].classList.contains('orient2')){
                piece_wrapper_div.innerHTML = `<img src='${red_laser_image}'/>`;
                piece_wrapper_div.style.transform = 'rotate(90deg)';
            }
        }

        //Only if the element has some peices in it, then wrap it. or else make the innerhtml of this to be nothing
        if(squares_fill_image[i].classList.contains('piece')){
            squares_fill_image[i].appendChild(piece_wrapper_div);
        } else{
            squares_fill_image[i].innerHTML = '';
        }
        
    }
}

//This will be a function that will use the class if html file and will return an array which will encode the information related to the chess board. So the function will return an array whcih is of the size (80*5), and this is for the following reason.
/**Information rlated to the piece are as follows:
 * For each piece I will need to have the piece type, piece color, piece points, piece orientation and then finally the peice position. So there are 5 numbers asscoiated to each position. And since there are 80 sqaures so 80*5 sized array.
 * Here is the rule to encode the board state.
 * 1) Piece_Color   =   1 (Red)     | 2(Blue)   | 0 (Nothing)     
 * 2) Piece_Type    =   1 (Mirror)  | 2 (Deflector) | 3 (Sheild)    | 4(King)   | 5 (laser) | 0(Nothing)
 * 3) Piece_Orientation =   1 | 2 | 3 | 4 | 0 (you know it)
 */

function makeEncode(depth){
    const code = [];
    //The first value would be the depth of the engine.
    code.push(depth);
    const squares = document.querySelectorAll('.square');
    for(let i=0;i<squares.length;i++){
        //This will be the position of the square
        code.push(i+1);

        //First the color and type
        if(squares[i].classList.contains('rmirror')){code.push(1); code.push(1);}
        else if(squares[i].classList.contains('rdeflector')){code.push(1); code.push(2);}
        else if(squares[i].classList.contains('rsheild')){code.push(1); code.push(3);}
        else if(squares[i].classList.contains('rking')){code.push(1); code.push(4);}
        else if(squares[i].classList.contains('rlaser')){code.push(1); code.push(5);}
        else if(squares[i].classList.contains('bmirror')){code.push(2); code.push(1);}
        else if(squares[i].classList.contains('bdeflector')){code.push(2); code.push(2);}
        else if(squares[i].classList.contains('bsheild')){code.push(2); code.push(3);}
        else if(squares[i].classList.contains('bking')){code.push(2); code.push(4);}
        else if(squares[i].classList.contains('blaser')){code.push(2); code.push(5);}
        else{
            code.push(0); code.push(0);
        }

        //This will encode the orientation of the piece
        if(squares[i].classList.contains('orient1')){code.push(1);}
        else if(squares[i].classList.contains('orient2')){code.push(2);}
        else if(squares[i].classList.contains('orient3')){code.push(3);}
        else if(squares[i].classList.contains('orient4')){code.push(4);}
        else{
            code.push(0);
        }
    }

    //Now that the code array is formed I return this.
    return code;
}
//This fucntion will be used to decode the server side response.The length of the encoded strig will always be 320, since it will just have the information about the pieces. And squares will have lenght 80 always
function makeDecode(encoded_array) {
    const squares = document.querySelectorAll('.square');

    if (encoded_array.length % 4 !== 0) {
        console.error('Invalid encoded array length:', encoded_array.length);
        return;
    }

    // Decode 4 values at a time
    for (let i = 0; i < encoded_array.length; i += 4) {
        const position = encoded_array[i] - 1;
        const color    = encoded_array[i + 1];
        const type     = encoded_array[i + 2];
        const orient   = encoded_array[i + 3];

        if (position < 0 || position >= squares.length) {
            console.error('Invalid position:', position + 1);
            continue;
        }

        if (color === 0) continue;

        const sq = squares[position];
        sq.classList.add('piece');

        // Red
        if (color === 1) {
            sq.classList.add('red');
            if (type === 1) sq.classList.add('rmirror');
            else if (type === 2) sq.classList.add('rdeflector');
            else if (type === 3) sq.classList.add('rsheild');
            else if (type === 4) sq.classList.add('rking');
            else if (type === 5) sq.classList.add('rlaser');
        }
        // Blue
        else if (color === 2) {
            sq.classList.add('blue');
            if (type === 1) sq.classList.add('bmirror');
            else if (type === 2) sq.classList.add('bdeflector');
            else if (type === 3) sq.classList.add('bsheild');
            else if (type === 4) sq.classList.add('bking');
            else if (type === 5) sq.classList.add('blaser');
        }

        if (orient >= 1 && orient <= 4) {
            sq.classList.add(`orient${orient}`);
        }
    }
}

/************************************   BOARD SETUP BUTTON CLICKED   *************************** */
//This is the click event listener to click on the option of board setup.
document.querySelectorAll('.setup-catalog-memember').forEach(setup => {
    setup.addEventListener('click', onSetupSelect);
});

let clicked; //Board that was clicked.
//This function is after a board set up is clicked.
function onSetupSelect(e){
    //console.log('Some setup has been clicked');
    //This will be the div that was clicked inside the board setu that will contain the informaton about the baord that wa clicked.
    clicked = e.currentTarget;
    //Back button appears
    back_button.style.display = 'block';
    //the complete set up has to disappear
    setup_catalog_container.style.display = 'none';
    //The depth and the player color form appaers
    form_container.style.display = 'flex';
    //Instructions will appear
    instruction_heading.innerHTML = "<h1>Prism's Gambit</h1>";
    instruction_content.innerHTML = "<p>You will have to select the depth of the engine and the color uou would like to play with</p>";
}

/************************************** FORM IS SUBMITTED ******************************* */



form.addEventListener('submit',function OnFormSubmit(e){
    //console.log('Submit Button is clicked');
    //Clear the Board
    document.querySelector('.board').innerHTML = '';
    e.preventDefault();

    //Form Updates
    const form_data = new FormData(form);
    depth = Number(form_data.get('depth_integer'));
    player_color = form_data.get('player-color');
    //console.log("depth = " + depth);
    //console.log('player color = ' + player_color);

    //Disappear the form
    form_container.style.display = 'none';

    //Create Board
    chessboard_container.style.display = 'flex';
    document.querySelector('.board').style.display = 'flex';
    let index = 1;
    //Empty Board (Adds sqaure class)
    for(let i=0;i<10;i++){
        const board_col = document.createElement('div');
        board_col.classList.add('col', `col${i+1}`);
        chessboard.appendChild(board_col);
        for(let j=0;j<8;j++){
            const board_row = document.createElement('div');
            board_row.classList.add('square');
            board_row.id = `square${index}`;
            //Will be used to make the game logic
            board_row.dataset.square = index;
            board_col.appendChild(board_row);
            index++;
        }
    }
    //Fills the piece class
    //console.log('Empty board created');
    if(clicked.classList.contains('ace')){
        instruction_heading.innerHTML = "<h1>Prism's Gambit (ACE)</h1>";
        instruction_content.innerHTML = '';
        //Now we can start filling the images
        document.getElementById('square1').classList.add('blue','blaser' ,'orient3','piece');
        document.getElementById('square4').classList.add('blue','bmirror','orient4','piece');
        document.getElementById('square5').classList.add('blue','bmirror', 'orient3','piece');
        document.getElementById('square18').classList.add('blue','bmirror', 'orient2','piece');
        document.getElementById('square20').classList.add('red','rmirror' ,'orient2','piece');
        document.getElementById('square21').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square24').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square27').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square32').classList.add('red','rsheild','orient1','piece');
        document.getElementById('square33').classList.add('blue','bsheild','orient3','piece');
        document.getElementById('square36').classList.add('blue','bdeflector','orient2','piece');
        document.getElementById('square37').classList.add('red','rdeflector','orient1','piece');
        document.getElementById('square40').classList.add('red','rking','orient0','piece');
        document.getElementById('square41').classList.add('blue','bking','orient0','piece');
        document.getElementById('square44').classList.add('blue','bdeflector','orient1','piece');
        document.getElementById('square45').classList.add('red','rdeflector','orient2','piece');
        document.getElementById('square48').classList.add('red','rsheild','orient1','piece');
        document.getElementById('square49').classList.add('blue','bsheild','orient3','piece');
        document.getElementById('square54').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square57').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square60').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square61').classList.add('blue','bmirror','orient4','piece');
        document.getElementById('square63').classList.add('red','rmirror','orient4','piece');
        document.getElementById('square76').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square77').classList.add('red','rmirror','orient2','piece');
        document.getElementById('square80').classList.add('red','rlaser','orient1','piece');  
    } else if(clicked.classList.contains('curiosity')) {
        instruction_heading.innerHTML = "<h1>Prism's Gambit (CURIOSITY)</h1>";
        instruction_content.innerHTML = '';
        document.getElementById('square1').classList.add('blue','blaser','orient3','piece');
        document.getElementById('square4').classList.add('blue','bmirror','orient4','piece');
        document.getElementById('square5').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square12').classList.add('red','rmirror','orient2','piece');
        document.getElementById('square13').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square24').classList.add('red','rdeflector','orient1','piece');
        document.getElementById('square27').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square30').classList.add('red','rmirror','orient2','piece');
        document.getElementById('square32').classList.add('red','rsheild','orient1','piece');
        document.getElementById('square33').classList.add('blue','bsheild','orient3','piece');
        document.getElementById('square36').classList.add('red','rmirror','orient3','piece');
        document.getElementById('square37').classList.add('red','rdeflector','orient1','piece');
        document.getElementById('square40').classList.add('red','rking','piece');
        document.getElementById('square41').classList.add('blue','bking','piece');
        document.getElementById('square44').classList.add('blue','bdeflector','orient1','piece');
        document.getElementById('square45').classList.add('blue','bmirror','orient1','piece');
        document.getElementById('square48').classList.add('red','rsheild','orient1','piece');
        document.getElementById('square49').classList.add('blue','bsheild','orient3','piece');
        document.getElementById('square51').classList.add('blue','bmirror','orient4','piece');
        document.getElementById('square54').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square57').classList.add('blue','bdeflector','orient1','piece');
        document.getElementById('square68').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square69').classList.add('blue','bmirror','orient4','piece');
        document.getElementById('square76').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square77').classList.add('red','rmirror','orient2','piece');
        document.getElementById('square80').classList.add('red','rlaser','orient1','piece');

    } else if(clicked.classList.contains('grail')) {
        //console.log('Into grail filler');
        instruction_heading = "<h1>Prism's Gambit (GRAIL)</h1>"
        instruction_content.innerHTML = '';
        document.getElementById('square1').classList.add('blue','blaser','orient3','piece');
        document.getElementById('square3').classList.add('blue','bmirror','orient4','piece');
        document.getElementById('square4').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square20').classList.add('blue','bdeflector','orient2','piece');
        document.getElementById('square29').classList.add('blue','bmirror','orient1','piece');
        document.getElementById('square30').classList.add('red','rdeflector','orient1','piece');
        document.getElementById('square32').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square33').classList.add('blue','bmirror','orient2','piece');
        document.getElementById('square35').classList.add('blue','bmirror','orient2','piece');
        document.getElementById('square36').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square38').classList.add('red','rsheild','orient1','piece');
        document.getElementById('square39').classList.add('red','rking','piece');
        document.getElementById('square40').classList.add('red','rsheild','orient1','piece');
        document.getElementById('square41').classList.add('blue','bsheild','orient3','piece');
        document.getElementById('square42').classList.add('blue','bking','piece');
        document.getElementById('square43').classList.add('blue','bsheild','orient3','piece');
        document.getElementById('square45').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square46').classList.add('red','rmirror','orient4','piece');
        document.getElementById('square48').classList.add('red','rmirror','orient4','piece');
        document.getElementById('square49').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square51').classList.add('blue','bdeflector','orient1','piece');
        document.getElementById('square52').classList.add('red','rmirror','orient3','piece');
        document.getElementById('square61').classList.add('red','rdeflector','orient2','piece');
        document.getElementById('square77').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square78').classList.add('red','rmirror','orient2','piece');
        document.getElementById('square80').classList.add('red','rlaser','orient1','piece');
    } else if(clicked.classList.contains('mercury')){
        instruction_heading.innerHTML = "<h1>Prism's Gambit (MERCURY)</h1>";
        instruction_content.innerHTML = '';
        document.getElementById('square1').classList.add('blue','blaser','orient4','piece');
        document.getElementById('square3').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square4').classList.add('blue','bmirror','orient4','piece');
        document.getElementById('square8').classList.add('blue','bdeflector','orient1','piece');
        document.getElementById('square13').classList.add('blue','bmirror','orient4','piece');
        document.getElementById('square27').classList.add('blue','bdeflector','orient1','piece');
        document.getElementById('square31').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square32').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square33').classList.add('blue','bmirror','orient2','piece');
        document.getElementById('square36').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square38').classList.add('red','rsheild','orient1','piece');
        document.getElementById('square39').classList.add('red','rsheild','orient1','piece');
        document.getElementById('square40').classList.add('red','rking','piece');
        document.getElementById('square41').classList.add('blue','bking','piece');
        document.getElementById('square42').classList.add('blue','bsheild','orient3','piece');
        document.getElementById('square43').classList.add('blue','bsheild','orient3','piece');
        document.getElementById('square45').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square48').classList.add('red','rmirror','orient4','piece');
        document.getElementById('square49').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square50').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square54').classList.add('red','rdeflector','orient1','piece');
        document.getElementById('square68').classList.add('red','rmirror','orient2','piece');
        document.getElementById('square73').classList.add('red','rdeflector','orient1','piece');
        document.getElementById('square77').classList.add('red','rmirror','orient2','piece');
        document.getElementById('square78').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square80').classList.add('red','rlaser','orient2','piece');
    } else if(clicked.classList.contains('sophie')) {
        instruction_heading.innerHTML = "<h1>Prism's Gambit (SOPHIE)</h1>";
        instruction_content.innerHTML = '';
        document.getElementById('square1').classList.add('blue','blaser','orient3','piece');
        document.getElementById('square3').classList.add('blue','bmirror','orient4','piece');
        document.getElementById('square6').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square7').classList.add('blue','bmirror','orient4','piece');
        document.getElementById('square21').classList.add('red','rdeflector','orient2','piece');
        document.getElementById('square22').classList.add('blue','bdeflector','orient1','piece');
        document.getElementById('square26').classList.add('blue','bsheild','orient3','piece');
        document.getElementById('square32').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square33').classList.add('blue','bking','piece');
        document.getElementById('square35').classList.add('blue','bmirror','orient2','piece');
        document.getElementById('square38').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square39').classList.add('red','rsheild','orient2','piece');
        document.getElementById('square40').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square41').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square42').classList.add('blue','bsheild','orient4','piece');
        document.getElementById('square43').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square46').classList.add('red','rmirror','orient4','piece');
        document.getElementById('square48').classList.add('red','rking','piece');
        document.getElementById('square49').classList.add('blue','bmirror','orient3','piece');
        document.getElementById('square55').classList.add('red','rsheild','orient1','piece');
        document.getElementById('square59').classList.add('red','rdeflector','orient1','piece');
        document.getElementById('square60').classList.add('blue','bdeflector','orient2','piece');
        document.getElementById('square74').classList.add('red','rmirror','orient2','piece');
        document.getElementById('square75').classList.add('red','rmirror','orient1','piece');
        document.getElementById('square78').classList.add('red','rmirror','orient2','piece');
        document.getElementById('square80').classList.add('red','rlaser','orient1','piece');
    }
    //Fills the images
    board_update();
    //console.log('Images are filled');

    //Add event listener to all the pieces
    addPieceEventListeners();
});
//Adds event listerners to all the movable piece
function addPieceEventListeners(){
    const piece = document.querySelectorAll('.piece');
    for (let i=0;i<piece.length;i++){
        //Adding event listner on blue
        if(player_color == 'blue'){
            if(piece[i].classList.contains('blue') && !piece[i].classList.contains('blaser')){
                piece[i].addEventListener('click',onPieceClick);
            }
        }
        if(player_color == 'red'){
            //Adding event listener on red
            if(piece[i].classList.contains('red') && !piece[i].classList.contains('rlaser')){
                piece[i].addEventListener('click',onPieceClick);
            }
        }
    }

}

/************************************** PIECE IS CLICKED TO MOVE OR ROTATE *****************************/



let clicked_piece;                      //Current piece clicked
let clicked_again = false;              //Are you clicking the same piece again
let previous_clicked_piece = null;      // Previously clicked piece
let piece_available_squares = [];       //Sqaures available to move for clicked piece
let filtered_squares = [];              

function onPieceClick(e){
    //console.log('A piece is clicked!');
    //console.log('Clicked again ? ' + clicked_again);
    //console.log('Previosly CLicked ? ' + previous_clicked_piece);
    clicked_piece = e.currentTarget;


    //Add class to the clicked piece
    clicked_piece.classList.add('Active_peice');

    if(previous_clicked_piece && previous_clicked_piece!=clicked_piece){
        //console.log('You had left a piece unclicked');
        previous_clicked_piece.style.transform = 'scale(1)';
        filtered_squares.forEach(c=>{
            c.style.backgroundColor = 'rgb(70, 70, 70)';
            c.removeEventListener('click',onMovedSqaureClick);
        });
        clicked_again = false;
        filtered_squares = [];
        piece_available_squares = [];

        //And finally add the eventlisteners to all the peicve again to listen
        addPieceEventListeners();
    }

    if(clicked_again){
        //console.log('You have clicked the piece again')
        clicked_piece.style.transform = 'scale(1)';
        //console.log('This should make color of the all the red sqaure grey again')
        clicked_piece.classList.remove('Active_peice');
        for(let i=0;i<filtered_squares.length;i++){
            filtered_squares[i].classList.remove('movable_sqaure');
            filtered_squares[i].style.backgroundColor = 'rgb(70, 70, 70)';
            filtered_squares[i].removeEventListener('click',onMovedSqaureClick);
        }
        document.querySelector('.rotate-button-container').style.display = 'none';
        piece_available_squares = [];
        filtered_squares = [];
        clicked_again = false;
        addPieceEventListeners();
        return;   
    }

    clicked_piece.style.transform = 'scale(1.2)';

    let clicked_piece_position = Number(clicked_piece.dataset.square);
    //console.log(`dataset_of_clicked_piece = ${dataset_of_clicked_piece}`);

    const top_edge = []; for(let k = 16;k<=72;k = k+8){top_edge.push(k);}
    const bottom_edge = []; for(let k=9;k<=65;k = k+8){bottom_edge.push(k);}
    //If the piece is at the right edge
    if(clicked_piece_position>1 && clicked_piece_position<8){
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+1}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-1}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+8}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+7}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+9}`));
    }
    //If the piece is at the left edge
    else if(clicked_piece_position>73 && clicked_piece_position<80){
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+1}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-1}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-8}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-7}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-9}`));
    }
    //If the piece is at the top edge
    else if(top_edge.includes(clicked_piece_position)){
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-8}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-9}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-1}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+7}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+8}`));
    }
    //if the piece is at the bottom edge
    else if(bottom_edge.includes(clicked_piece_position)){
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-8}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-7}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+1}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+9}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+8}`));
    }
    //If the piece is at the right top corner
    else if(clicked_piece_position === 8){
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-1}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+7}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+8}`));
    }
    //If the piece is at the left bottom corner
    else if(clicked_piece_position === 73){
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+1}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-8}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-7}`));
    }
    //if the peice is just anywhere, other then the edges and corner, then I can move in all the direction by one step
    else if(clicked_piece_position<80 && clicked_piece_position>1){
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-1}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-7}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-8}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position-9}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+1}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+8}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+9}`));
        piece_available_squares.push(document.getElementById(`square${clicked_piece_position+7}`));
    }

    //console.log(piece_available_squares);
    //Remove the available position from the above array that already has some other piece.
    filtered_squares = piece_available_squares.filter(c =>
        !c.classList.contains('piece')
    )

    //Add class to filtered sqaures
    for(let i=0;i<filtered_squares.length;i++){
        filtered_squares[i].classList.add('movable_sqaure');
    }

    //If the piece wants to move or rotate (make available spaces red and rotate button appear)
    addEventListenerAllMoveablePeice();
    
    previous_clicked_piece = clicked_piece;
    clicked_again = true;
}

function addEventListenerAllMoveablePeice(){
    //If the piece is avalibale to move to.
    const movable_squares = document.querySelectorAll('.movable_sqaure');
    for(let i=0;i<movable_squares.length;i++){
        movable_squares[i].style.backgroundColor = 'red';
        if(movable_squares[i])movable_squares[i].removeEventListener('click', onMovedSqaureClick);
        movable_squares[i].addEventListener('click', onMovedSqaureClick);
    }
    e = document.querySelector('.Active_peice');
    //If the piece is mirror, sheild or deflector (Rotatable)
    if(
        e.classList.contains('rmirror') ||
        e.classList.contains('bmirror') ||
        e.classList.contains('rdeflector') ||
        e.classList.contains('bdeflector') ||
        e.classList.contains('rsheild') ||
        e.classList.contains('bsheild')||
        e.classList.contains('rlaser') ||
        e.classList.contains('blaser')
    ){
        //console.log('rotate eventlisteners are added');
        document.querySelector('.rotate-button-container').style.display = 'flex';
    }
    const rotate_button = document.querySelectorAll('.rotate-button');
    for(let i=0;i<rotate_button.length;i++){
        if(rotate_button[i])rotate_button[i].removeEventListener('click',onRotateSqaureClick);
        rotate_button[i].addEventListener('click',onRotateSqaureClick);
    }
}

/**********************************TO SLEEP THE PROGRAM FOR ANIMATION ***************************/
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}



/******************************************* MOVED SQAURE CLICKED *************************/
async function onMovedSqaureClick(e){
    document.querySelector('.rotate-button-container').style.display = 'none';

    //console.log('So you want to move at ' + e.currentTarget);
    clicked_piece.classList.remove('Active_peice');
    for(let i=0;i<filtered_squares.length;i++){
        filtered_squares[i].classList.remove('movable_sqaure');
        filtered_squares[i].style.backgroundColor = 'rgb(70, 70, 70)';
    }
    clicked_piece.style.transform = 'scale(1)';
    // //Change the clicked piece class
    for(let i=1;i<clicked_piece.classList.length;i++){
        e.currentTarget.classList.add(clicked_piece.classList[i]);
    }
    clicked_piece.className = 'square';

    //Render the new board.
    board_update();

    //Animate the blue laser
    animateLaser('blue');
    await sleep(4000);//Program sleeps for 4 seconds

    //Now the board should be used to make the encoded list of numbers
    let encode = [];
    let decode = [];

    encode = makeEncode(depth);
    console.log(encode);
    console.log(encode.join(" "));




    //Check if the game is over
    if (isGameOver()) {
        chessboard_container.style.display = 'none';
    }
    
    fetch("/solve", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ encoded_array: encode })
    })
    .then(res => res.json())
    .then(async(data) => {
        decode = data.board.split(' ').map(Number);
        console.log("This is the computer's move");
        console.log(decode);
        //Then clone the board and this will only contain the html class and not the event listeners associated to previous board.
        document.querySelector('.board').innerHTML = '';
        //Makes the empty board
        let index = 1;
        for(let i=0;i<10;i++){
            const board_col = document.createElement('div');
            board_col.classList.add('col', `col${i+1}`);
            chessboard.appendChild(board_col);
            for(let j=0;j<8;j++){
                const board_row = document.createElement('div');
                board_row.classList.add('square');
                board_row.id = `square${index}`;
                //Will be used to make the game logic
                board_row.dataset.square = index;
                board_col.appendChild(board_row);
                index++;
            }
        }

        
        
        //Updates the classes based on deocoded array
        makeDecode(decode);
        

        //After the animation is done I remove the canvas
        //canvas.style.display='none';
        


        //Adds the images based on the classes
        board_update();

        //Check if the game is over
        if (isGameOver()) {
            chessboard_container.style.display = 'none';
        }

        //Make the animation for red laser
        animateLaser('red');
        await sleep(4000);



        //Add the event listeners to all the squares again
        addPieceEventListeners();
        addBackButtonEventListener();
        filtered_squares = [];
        piece_available_squares = [];
        previous_clicked_piece = null;
        clicked_again = false;
        console.log(`Check the HTML document for the updated classes`);
        })
    .catch(err => console.error(err));
    
    
    
}

/******************************************** ROTATE SQAURE CLICKED ************************ */
async function onRotateSqaureClick(e){

    document.querySelector('.rotate-button-container').style.display = 'none';

    clicked_piece.classList.remove('Active_peice');

        for(let i=0;i<filtered_squares.length;i++){
            filtered_squares[i].classList.remove('movable_sqaure');
            filtered_squares[i].style.backgroundColor = 'rgb(70, 70, 70)';
        }


        clicked_piece.style.transform = 'scale(1)';

        console.log('Want to rotate clicked piece Clockwise');
    //Class are updated
    if(e.currentTarget.classList.contains('clockwise-rotate')){
        //If the piece is mirror or sheild
        if(
            clicked_piece.classList.contains('rmirror') ||
            clicked_piece.classList.contains('bmirror') ||
            clicked_piece.classList.contains('rsheild') ||
            clicked_piece.classList.contains('bsheild')
        ){
            if(clicked_piece.classList.contains('orient1')){clicked_piece.classList.replace('orient1','orient4');}
            else if(clicked_piece.classList.contains('orient2')){clicked_piece.classList.replace('orient2','orient1');}
            else if(clicked_piece.classList.contains('orient3')){clicked_piece.classList.replace('orient3','orient2');}
            else if(clicked_piece.classList.contains('orient4')){clicked_piece.classList.replace('orient4','orient3');}
        }     
        
        //If the piece is deflector
        if(clicked_piece.classList.contains('rdeflector') || clicked_piece.classList.contains('bdeflector')){
            if(clicked_piece.classList.contains('orient1')){clicked_piece.classList.replace('orient1','orient2');}
            else if(clicked_piece.classList.contains('orient2')){clicked_piece.classList.replace('orient2','orient1');}
        }
        //If the piece is laser
        //If the piece is laser
        if(clicked_piece.classList.contains('rlaser') || clicked_piece.classList.contains('blaser')){
            if(clicked_piece.classList.contains('orient1')){clicked_piece.classList.replace('orient1','orient3');}
            else if(clicked_piece.classList.contains('orient3')){clicked_piece.classList.replace('orient2','orient1');}
        }
    }
    else if(e.currentTarget.classList.contains('anti-clockwise-rotate')){
        //If the piece is mirror or sheild
        if(
            clicked_piece.classList.contains('rmirror') ||
            clicked_piece.classList.contains('bmirror') ||
            clicked_piece.classList.contains('rsheild') ||
            clicked_piece.classList.contains('bsheild')
        ){
            if(clicked_piece.classList.contains('orient1')){clicked_piece.classList.replace('orient1','orient2');}
            else if(clicked_piece.classList.contains('orient2')){clicked_piece.classList.replace('orient2','orient3');}
            else if(clicked_piece.classList.contains('orient3')){clicked_piece.classList.replace('orient3','orient4');}
            else if(clicked_piece.classList.contains('orient4')){clicked_piece.classList.replace('orient4','orient1');}
        }     
        
        //If the piece is deflector
        if(clicked_piece.classList.contains('rdeflector') || clicked_piece.classList.contains('bdeflector')){
            if(clicked_piece.classList.contains('orient1')){clicked_piece.classList.replace('orient1','orient2');}
            else if(clicked_piece.classList.contains('orient2')){clicked_piece.classList.replace('orient2','orient1');}
        }

        //If the piece is laser
        if(clicked_piece.classList.contains('rlaser') || clicked_piece.classList.contains('blaser')){
            if(clicked_piece.classList.contains('orient1')){clicked_piece.classList.replace('orient1','orient3');}
            else if(clicked_piece.classList.contains('orient3')){clicked_piece.classList.replace('orient2','orient1');}
        }
    }

    //Render the new board.
    board_update();

    //Animate blue laser
    animateLaser('blue');
    await sleep(4000);//Program sleeps for 4 seconds

    let encode = [];
    let decode = [];

    encode = makeEncode(depth);

    //Check if the game is over
    if (isGameOver()) {
        chessboard_container.style.display = 'none';
    }
     


    console.log(encode);

    

    fetch("/solve", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ encoded_array: encode })
    })
    .then(res => res.json())
    .then(async(data) => {
        decode = data.board.split(' ').map(Number);
        console.log("This is the computer's move");
        console.log(decode);
        //Then clone the board and this will only contain the html class and not the event listeners associated to previous board.
        document.querySelector('.board').innerHTML = '';
        //Makes the empty board
        let index = 1;
        for(let i=0;i<10;i++){
            const board_col = document.createElement('div');
            board_col.classList.add('col', `col${i+1}`);
            chessboard.appendChild(board_col);
            for(let j=0;j<8;j++){
                const board_row = document.createElement('div');
                board_row.classList.add('square');
                board_row.id = `square${index}`;
                //Will be used to make the game logic
                board_row.dataset.square = index;
                board_col.appendChild(board_row);
                index++;
            }
        }
        
        //Updates the classes based on deocoded array
        makeDecode(decode);
        

        //After the animation is done I remove the canvas
        //canvas.style.display='none';
        


        //Adds the images based on the classes
        board_update();

        //Animate red laser
        animateLaser('red');
        await sleep(4000);//Program sleeps for 4 seconds
        

        //Add the event listeners to all the squares again
        addPieceEventListeners();
        addBackButtonEventListener();
        filtered_squares = [];
        piece_available_squares = [];
        previous_clicked_piece = null;
        clicked_again = false;
        //console.log(`Check the HTML document for the updated classes`);
        clicked_again = false;
        previous_clicked_piece = null;

        //Check if the game is over
        isGameOver();
    })
    .catch(err => console.error(err));

}

/**************************************CHECK IF THE GAME IS OVER ******************* */
function isGameOver() {
    //console.log("Checking if the game is over");
    const pieces = document.querySelectorAll('.piece');

    let redKingExists = false;
    let blueKingExists = false;

    pieces.forEach(piece => {
        if (piece.classList.contains('rking')) redKingExists = true;
        if (piece.classList.contains('bking')) blueKingExists = true;
    });

    if (!redKingExists || !blueKingExists) {
        alert(!redKingExists ? 'Blue won the game' : 'Red won the game');
        return true;
    }
    return false;
}

/************************************* LASER ANIMATION **************** */
function animateLaser(color){

    //console.log('Into Animate Laser Function');

    let path = [];//Stores the path laser has travelled

    const blue_laser = document.querySelector('.blaser');
    const red_laser = document.querySelector('.rlaser');

    let tracer_direction = 0;
    let tracer_position = 0;

    if(color === 'red'){
        //Tracer initially at red laser
        tracer_position = 80;

        //Will make the location of divs that needs to be colored red
        if(red_laser.classList.contains('orient1')){
            //Red laser orinted towards you
            tracer_direction = -1;//Moves Down

        } else if(red_laser.classList.contains('orient2')){
            //Red laser oriented towards right
            tracer_direction = -8;//Moves Right
        }

        let laserHit = false;
        let laserBlocked = false;

        //Now move the laser
        while(!laserEscaped(tracer_position,tracer_direction) || !laserHit || !laserBlocked){

            //console.log("Advancing the lazer");
            //console.log('Laser position : ' + tracer_position);

            //Advance the laser once and store the location
            tracer_position = tracer_position + tracer_direction;
            path.push(tracer_position);


            //Look if a piece is hit by a piece
            let tracer_element = document.querySelector(`square${tracer_position}`);

            //Update the tracer value for the advancing the laser
            tracer_direction = updateTracer(tracer_element,tracer_direction);

            if(tracer_direction === 0){
                //console.log("Laser has killed a piece or is blocked by it");
                laserHit = true;
            }
        }
    }
    else if(color == 'blue'){
        //Tracer initially at blue laser
        tracer_position = 1;

        //Will make the location of divs that needs to be colored red
        if(blue_laser.classList.contains('orient3')){
            //Red laser orinted towards you
            tracer_direction = +1;//Moves up

        } else if(blue_laser.classList.contains('orient4')){
            //Red laser oriented towards right
            tracer_direction = +8;//Moves down
        }

        let laserHit = false;
        let laserBlocked = false;

        let debug = 0;

        //console.log('Going to enter the while loop');
        //Now move the laser
        while(!laserEscaped(tracer_position,tracer_direction) && !laserHit && !laserBlocked && debug<20){
            debug++;
            

            //Advance the laser once and store the location
            tracer_position = tracer_position + tracer_direction;
            path.push(tracer_position);

            //console.log("Advancing the lazer");
            //console.log('Laser position : ' + tracer_position);
            //console.log('Laser Direction : ' + tracer_direction);

            //Look if a piece is hit by a piece
            let tracer_element = document.getElementById(`square${tracer_position}`);

            //console.log(`Class List of element at this location is : ${tracer_element.classList}`);

            //Update the tracer value for the advancing the laser
            tracer_direction = updateTracer(tracer_element,tracer_direction);

            //console.log('After updating the Laser direction : ' + tracer_direction);

            if(tracer_direction === 0){
                //console.log("Laser has killed a piece or is blocked by it");
                laserHit = true;
            }
        }
    }

    //Print the values inside the path
    //console.log('Path is this : ' + path);
    
    //using the values of path, now we make those squares red or blue
    for(let i=0;i<path.length;i++){
        document.getElementById(`square${path[i]}`).style.backgroundColor = color;
    }

}

//For a given tracer location which if does have a peice, this function will update the value of tracer_direction and will return it.
function updateTracer(tracer_element,tracer_direction){

    //console.log('Inside updateTracer Function');
    //console.log(`Class List of element at this location is : ${tracer_element.classList}`);
    

    //Laser encounters King
    if(tracer_element.classList.contains('bking') || tracer_element.classList.contains('rking')){
        return -1;
    }
    //If the tracer is travelling down the board
    if(tracer_direction === -1){
        //Laser encounters Mirror
        if(tracer_element.classList.contains('bmirror') || tracer_element.classList.contains('rmirror')){
            if(tracer_element.classList.contains('orient1') || tracer_element.classList.contains('orient4')){return 0;}
            else if(tracer_element.classList.contains('orient2')){return (-8);}
            else if(tracer_element.classList.contains('orient3')){return (+8);}
        }
        //Laser encounters Sheild
        else if(tracer_element.classList.contains('bsheild') || tracer_element.classList.contains('rsheild')){
            return 0;
        }
        //laser encounters Deflector
        else if(tracer_element.classList.contains('bdeflector') || tracer_element.classList.contains('rdeflector')){
            if(tracer_element.classList.contains('orient1')){return +8;}
            else return -8;
        } 
    }
    //if the tracer is travelling up the board 
    else if(tracer_direction === +1){
        //Laser encounters Mirror
        if(tracer_element.classList.contains('bmirror') || tracer_element.classList.contains('rmirror')){
            if(tracer_element.classList.contains('orient2') || tracer_element.classList.contains('orient3')){return 0;}
            else if(tracer_element.classList.contains('orient1')){return (-8);}
            else if(tracer_element.classList.contains('orient4')){return (+8);}
        }
        //Laser encounters Sheild
        else if(tracer_element.classList.contains('bsheild') || tracer_element.classList.contains('rsheild')){
            return 0;
        }
        //laser encounters Deflector
        else if(tracer_element.classList.contains('bdeflector') || tracer_element.classList.contains('rdeflector')){
            if(tracer_element.classList.contains('orient1')){return -8;}
            else if(tracer_element.classList.contains('orient2')){return +8;}
        } 
    }
    //if the laser is travelling to left
    else if(tracer_direction === +8){
        //Laser encounters Mirror
        if(tracer_element.classList.contains('bmirror') || tracer_element.classList.contains('rmirror')){
            if(tracer_element.classList.contains('orient3') || tracer_element.classList.contains('orient4')){return 0;}
            else if(tracer_element.classList.contains('orient1')){return (-1);}
            else if(tracer_element.classList.contains('orient2')){return (+1);}
        }
        //Laser encounters Sheild
        else if(tracer_element.classList.contains('bsheild') || tracer_element.classList.contains('rsheild')){
            return 0;
        }
        //laser encounters Deflector
        else if(tracer_element.classList.contains('bdeflector') || tracer_element.classList.contains('rdeflector')){
            if(tracer_element.classList.contains('orient1')){return -8;}
            else if(tracer_element.classList.contains('orient2')){return +8;}
        }
    }
    //If the laser is travelling to right
    else if(tracer_direction === -8){
        //Laser encounters Mirror
        if(tracer_element.classList.contains('bmirror') || tracer_element.classList.contains('rmirror')){
            if(tracer_element.classList.contains('orient2') || tracer_element.classList.contains('orient1')){return 0;}
            else if(tracer_element.classList.contains('orient3')){return (+1);}
            else if(tracer_element.classList.contains('orient4')){return (-1);}
        }
        //Laser encounters Sheild
        else if(tracer_element.classList.contains('bsheild') || tracer_element.classList.contains('rsheild')){
            return 0;
        }
        //laser encounters Deflector
        else if(tracer_element.classList.contains('bdeflector') || tracer_element.classList.contains('rdeflector')){
            if(tracer_element.classList.contains('orient1')){return +8;}
            else if(tracer_element.classList.contains('orient2')){return -8;}
        }
    }

    return tracer_direction;
}

// For a given laser location and direction it says if the laser has escaped or not.
function laserEscaped(tracer_position,tracer_direction){
    const tracer_location = document.querySelectorAll('.square')[tracer_position];
    //console.log('Debugging the escape lazer function');
    //console.log('Laser Position : ' + tracer_position);
    //console.log('Laser Direction : ' + tracer_direction);

    //If the position at which tracer lies on the board doesn't contain any piece
    if(!tracer_location.classList.contains('piece')){
        //And if it's direction is such that it will escape if it is advanced
        //If the tracer is at left edge
        if((tracer_position<=80 && tracer_position>=73) && tracer_direction === +8){return true;}
        //If the tracer is at right edge
        else if((tracer_position<=8 && tracer_position>=1) && tracer_direction === -8){return true;}
        //If the tracer is at bottom edge
        else if((tracer_position%8 === 1) && tracer_direction === -1){return true;}
        //If tracer is at thre top edge
        else if((tracer_position%8 === 0) && tracer_direction === +1){return true;}
    } else {
        //console.log('Laser did not escape');
        return false;
    }
    
}


/****************************************  BACK BUTTON  ********************************** */
function addBackButtonEventListener(){
    if(document.querySelector('.back_button')){
        document.querySelector('.back_button').removeEventListener('click',onBackClick);
    }
    
    document.querySelector('.back-button').addEventListener('click',onBackClick);
}
back_button.addEventListener('click' , onBackClick);
function onBackClick(){
    //Clear the canvas
    const canvas = document.querySelector('#laser-canvas');
    //canvas.display.style = 'none';
    //Clear the board 
    document.querySelector('.board').innerHTML = '';
    //Hide the back button
    back_button.style.display = 'none';
    //Hide the rotate button
    document.querySelector('.rotate-button-container').style.display = 'none';
    //Hide the board
    chessboard_container.style.display = 'none';
    //Hide the form
    form_container.style.display = 'none';
    //And then reappaer the setup container
    setup_catalog_container.style.display = 'flex';

    instruction_heading.innerHTML = "<h1>Prism's Gambit</h1>";

    instruction_content.innerHTML = "<p>How did you like the game? If there is any suggestions related to, your likes or dislikes about the game, please email me from the mail ID given below. I would be happy to know from you</p><p>You may also try other setups of the game.</p>";
    
}