
const principal =() => {


      const loadData = () => {
        const xhr = new XMLHttpRequest()
        xhr.open("GET", "192.168.100.9/leitura")
        xhr.send(null)
        xhr.onreadystatechange = () => {
            if(xhr.readyState === 4){
                const teste = xhr.responseText
                const resposta = JSON.parse(xhr.responseText)
                console.log(resposta)
                const PortaoPeq = resposta.PP
                const PortaoGrd = resposta.PG
                const InfraSala = resposta.IS
                const InfraCozinha = resposta.IC


                if(PortaoPeq == "ON"){
                    document.getElementById("sensor-portao-peq").classList.remove('sensor-portao-peq-normal');
                    document.getElementById("sensor-portao-peq").classList.add('sensor-portao-peq-alarmado');
                }else {
                    document.getElementById("sensor-portao-peq").classList.remove('sensor-portao-peq-alarmado');
                    document.getElementById("sensor-portao-peq").classList.add('sensor-portao-peq-normal');
                }

                if(PortaoGrd == "ON"){
                    document.getElementById("sensor-portao-grd").classList.remove('sensor-portao-grd-normal');
                    document.getElementById("sensor-portao-grd").classList.add('sensor-portao-grd-alarmado');
                }else {
                    document.getElementById("sensor-portao-grd").classList.remove('sensor-portao-grd-alarmado');
                    document.getElementById("sensor-portao-grd").classList.add('sensor-portao-grd-normal');
                }

                if(InfraSala == "ON"){
                    document.getElementById("sensor-infra-sala").classList.remove('sensor-infra-sala-normal');
                    document.getElementById("sensor-infra-sala").classList.add('sensor-infra-sala-alarmado');
                }else {
                    document.getElementById("sensor-infra-sala").classList.remove('sensor-infra-sala-alarmado');
                    document.getElementById("sensor-infra-sala").classList.add('sensor-infra-sala-normal');
                }

                if(InfraCozinha == "ON"){
                    document.getElementById("sensor-infra-coz").classList.remove('sensor-infra-coz-normal');
                    document.getElementById("sensor-infra-coz").classList.add('sensor-infra-coz-alarmado');
                }else {
                    document.getElementById("sensor-infra-coz").classList.remove('sensor-infra-coz-alarmado');
                    document.getElementById("sensor-infra-coz").classList.add('sensor-infra-coz-normal');
                }


            }
        }
    }

    // buttonEl.addEventListener("click", loadData)
    setInterval(loadData, 1000);


}

document.addEventListener("DOMContentLoaded", principal)
