function func0(a, b){
  let result = "Вартість замовлення: " + a

  if(a%5===0){
    result+=" гривень "
  } else if(a===2 || a===4){
    result+=" гривні "
  } else
    result+=" гривня "

  result+=b

  if(b%10 === 2 || b%10 === 3 || b%10 === 4){
      result+=" копійки "
  } else if(b%10 === 1){
      result+=" копійка "
  } else
      result+=" копійок "
    
  console.log(result)
}


let func1 = function(a,b){
  func0(a,b)
}

let func2 = (a,b) => func1(a,b)

func0(5,2)