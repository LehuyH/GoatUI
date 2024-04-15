const genID = () => "state"+Math.random().toString(36).substring(2, 9) + Date.now().toString(36)

window.reactives = new Map()

window.createReactive = (value) => {
  const id = genID()
  reactives.set(id, value)
  return id 
}

let app = null

window.mount = ()=>{
  const { createApp } = Vue

  app = createApp({
    data() {
      return Object.fromEntries(reactives.entries())
    },
    methods:{
      callEventListenerWithValue(value, reactiveID){
        if(typeof value !== 'number'){
          _callEventListenerWithValue(reactiveID,stringToNewUTF8(value))
        }else{
          _callEventListenerWithValue(reactiveID,value)
        }
      }
    }
    
  }).mount('#app')

}

window.setState = (reactiveID, value) => {
  app[reactiveID] = value
}