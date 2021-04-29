let calc_distance = (x1,x2,y1,y2) => {return Math.sqrt( Math.pow((x1-x2), 2) + Math.pow((y1-y2), 2))}

let get_quadrant = function(x,y){
  if(x>0 && y>0){
    return 1;
  } else if(x<0 && y>0){
    return 2;
  } else if(x<0 && y<0){
    return 3;
  } else if(x>0 && y<0)
    return 4;
  else return -1;
}

function task(x1, y1, x2, y2){

  let quadrant1 = get_quadrant(x1,y1)
  let quadrant2 = get_quadrant(x2,y2)

  if(quadrant1==quadrant2 && quadrant1!=-1)  {
    console.log(calc_distance(x1,x2,y1,y2))
  } else {
    console.log(quadrant1 + " " + quadrant2);
  } 
}

task(5,2,-2,3)