function func0(n){
  for(let i=1; i<=n; i++){
    if(i%3===0 && i%5===0){     
        console.log('fizzbuzz')
    } else if(i%3===0){     
        console.log('fizz')
    } else if(i%5===0){
        console.log('buzz')
    } else
        console.log(i)
  }
}

let func1 = function(n) {func0(n)}
let func2 = (n) => {func0(n)}

func0(5)