
#include <SFML/Graphics.hpp>

#include <optional>
#include <vector>
#include <iostream>

using std::vector; 
using std::cout; 

// struct for rows and columns
struct gridCell{
    int row;
    int col;
    bool isWall;

};

//node
struct node{
    int row;
    int col;
    //cost
    int g;
    //estimate cost
    int h;
    //g+h, used to sort
    int f;
    bool open;
    int parentRow;
    int parentCol;
};

node openSet[20][30];

int distance(int row, int endRow,int col, int endCol){
return abs(endRow - row) + abs(endCol - col);
}


int main()
{
    constexpr unsigned int windowWidth = 1000;
    constexpr unsigned int windowHeight = 700;

    constexpr int columns = 30;
    constexpr int rows = 20;

    vector<vector<gridCell>> grid(rows, vector<gridCell>(columns, gridCell{0,0,false})); 


//initilaize the grid struct
    for(int i =0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            grid[i][j].row = i;
            grid[i][j].col = j;
            grid[i][j].isWall = false;
            }
        }

//wall
        for(int i = 0; i < rows; i++){
            grid[i][15].isWall = true;
        }
        grid[3][15].isWall = false;

//start
vector<int> start(2);
start[0]=0;
start[1]=0;
//end
vector<int> end(2);
end[0] = 19;
end[1] = 29;

//initalize openset
for(int i= 0; i < 20; i++){
    for(int j= 0; j < 30; j++){
        openSet[i][j].row = i;
        openSet[i][j].col = j;
        openSet[i][j].g = 1000;
        openSet[i][j].h = distance(i, end[0], j, end[1]);
        openSet[i][j].f = openSet[i][j].g + openSet[i][j].h;
        openSet[i][j].open = false;
    }
}


openSet[start[0]][start[1]].g = 0;
openSet[start[0]][start[1]].f = openSet[start[0]][start[1]].g + openSet[start[0]][start[1]].h;
openSet[start[0]][start[1]].open = true;


int count = 1;
while(count > 0){
    int bestRow = -1; 
    int bestCol = -1;

    for(int i= 0; i < 20; i++){
      for(int j = 0; j < 30; j++){
        if(bestRow < 0 ||openSet[i][j].f < openSet[bestRow][bestCol].f ){
            bestRow = i;
            bestCol = j;
            }            
       }       
    } 

    if(bestRow == end[0] && bestCol == end[1]){ 
        std::cout << "Found";
        break; 
     }

    if(bestRow -1 >= 0){
        if(grid[bestRow -1][bestCol].isWall){
            continue;
        }
    if(!grid[bestRow -1][bestCol].isWall){
            openSet[bestRow-1][bestCol].g = openSet[bestRow-1][bestCol].g + 1 ;
            openSet[bestRow-1][bestCol].f = openSet[bestRow-1][bestCol].g + openSet[bestRow-1][bestCol].h;
            openSet[bestRow-1][bestCol].parentRow = bestRow;
            openSet[bestRow-1][bestCol].parentCol = bestCol;
            openSet[bestRow-1][bestCol].open = true;
        }
    }

    if(bestRow + 1 < grid.size()){
        if(grid[bestRow +1][bestCol].isWall){
            continue;
        }
    if(!grid[bestRow +1][bestCol].isWall){
            openSet[bestRow+1][bestCol].g = openSet[bestRow+1][bestCol].g + 1 ;
            openSet[bestRow+1][bestCol].f = openSet[bestRow+1][bestCol].g + openSet[bestRow+1][bestCol].h;
            openSet[bestRow+1][bestCol].parentRow = bestRow;
            openSet[bestRow+1][bestCol].parentCol = bestCol;
            openSet[bestRow+1][bestCol].open = true;
        }
        count++;
    }


    count--; 
}

    constexpr float cellSize = 30.0F;

    sf::RenderWindow window(
        sf::VideoMode({windowWidth, windowHeight}),
        "Pathfinding Visualizer"
    );

    window.setFramerateLimit(60);

    while (window.isOpen()){
        while (const std::optional<sf::Event> event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color(24, 28, 36));

        
//makes the image grid
        for (int row = 0; row < rows; ++row)
        {
            for (int column = 0; column < columns; ++column)
            {
                sf::RectangleShape cell({cellSize - 1.0F, cellSize - 1.0F});

                cell.setPosition({
                    static_cast<float>(column) * cellSize,
                    static_cast<float>(row) * cellSize
                });




//reads the grid 
if(grid[row][column].isWall == true){
    cell.setFillColor(sf::Color(255, 0, 0));
}
else if(grid[row][column].row == start[0] && grid[row][column].col == start[1]){
    cell.setFillColor(sf::Color(255, 215, 0));
}
else if(grid[row][column].row == end[0] && grid[row][column].col == end[1]){
    cell.setFillColor(sf::Color(0,255,0));
}

else {
    cell.setFillColor(sf::Color(50, 60, 75));
}

                window.draw(cell);
            }
        }

        window.display();
    }
    return 0;
}