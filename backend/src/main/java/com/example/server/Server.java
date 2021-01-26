package com.example.server;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.SequenceGenerator;
import javax.persistence.TableGenerator;


@Entity
@Table(name = "server")
public class Server implements Serializable {

    private static final long serialVersionUID = -2343243243242432341L;
    @Id
//    @GeneratedValue
//    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "user_id_seq")
    @SequenceGenerator(name = "user_id_seq", sequenceName = "user_id_seq", allocationSize = 1)
//    @GeneratedValue(strategy = GenerationType.TABLE, generator = "table_generator")
//    @TableGenerator(name = "table_generator", table = "dep_ids", pkColumnName = "seq_id", valueColumnName = "seq_vale")

    private int user_id_seq;

    @Column(name = "id")
    private String id;

    @Column(name = "temperature")
    private Double temperature;

    @Column(name = "humidity")
    private Double humidity;

    @Column(name = "time")
    private String time;

    @Column(name = "longitude")
    private Double longitude;

    @Column(name = "latitude")
    private Double latitude;

    @Column(name = "status")
    private Boolean status;

    @Column(name = "trip")
    private String trip;

    protected Server() {
    }

    public Server(Double temperature, Double humidity, String time, String id, Double longitude, Double latitude, Boolean status, String trip) {
        this.user_id_seq = 0;
        this.temperature = temperature;
        this.humidity = humidity;
        this.time = time;
        this.id = id;
        this.longitude = longitude;
        this.latitude = latitude;
        this.status = status;
        this.trip = trip;
    }

//    public String toString() {
//        return String.format("Customer[id=%d, firstName='%s', lastName='%s']", id, firstName, lastName);
//    }
    public Double getTemperature() {
        return temperature;
    }
    public Double getHumidity() {
        return humidity;
    }
    public String getTime() {
        return time;
    }
    public String getId() {
        return id;
    }
    public Double getLongitude() {
        return longitude;
    }
    public Double getLatitude() {
        return latitude;
    }
    public Boolean getStatus() {
        return status;
    }
    public String getTrip() {
        return trip;
    }

    public void setId(String id) { this.id = id;
    }
}