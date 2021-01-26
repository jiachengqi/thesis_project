package com.example.server;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


@RestController
public class Controller {
    @Autowired
    ServerRepo serverRepo;

    @GetMapping("/create")
    public String create(){
        // save a single Customer
        serverRepo.save(new Server(12.0,13.0,"199505","1",3.1,3.5,true,"199509"));

        return "Server is created";
    }



    @RequestMapping(value = "/server", method = RequestMethod.POST)
    public ResponseEntity<String> createWithInfo(@RequestBody Server server){
        serverRepo.save(server);
        return new ResponseEntity(HttpStatus.CREATED);
    }


    @RequestMapping("/search/{id}")
    public String search(@PathVariable int id){
        String server = "";
        server = serverRepo.findById(id).toString();
        return server;
    }


    @RequestMapping(value = "/get/{id}", method = RequestMethod.GET)
    public List<Server> getById(@PathVariable String id){
        List<Server> stringList = new ArrayList<Server>() {
        };
        for (Server server : serverRepo.findAll()){
            if (server.getId().equals(id))
            stringList.add(server);
        }
        return stringList;

    }


    @RequestMapping(value = "/getall", method = RequestMethod.GET)
    public List<Server> getall(){
        List<Server> stringList = new ArrayList<Server>() {
        };
        for (Server server : serverRepo.findAll()){
            stringList.add(server);
        }
        return stringList;

        }





//    @GetMapping("/addd/{parameter}")


//    @RequestMapping(value = "/{parameter}", method = RequestMethod.POST)
//    public String createWithInfo(@PathVariable String parameter){
//        ArrayList<String> e = new ArrayList<>(Arrays.asList(parameter.split(",")));
//        Double temperature = Double.parseDouble(e.get(0));
//        Double humidity = Double.parseDouble(e.get(1));
//        String time = e.get(2);
//        int id = Integer.parseInt(e.get(3));
//        Double longitude = Double.parseDouble(e.get(4));
//        Double latitude = Double.parseDouble(e.get(5));
//        serverRepo.save(new Server( temperature,  humidity,  time,  id, longitude, latitude));
//        return "done!";
//    }


}