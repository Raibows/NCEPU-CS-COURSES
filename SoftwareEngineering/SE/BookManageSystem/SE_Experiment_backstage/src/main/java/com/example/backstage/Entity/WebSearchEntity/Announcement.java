package com.example.backstage.Entity.WebSearchEntity;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;
import java.util.Date;

@Entity
@Data
@Table(name = "announcement")
public class Announcement {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
    private String title;
    private String content;
    private int type;
    @JsonFormat(pattern = "yyyy-MM-dd")
    private Date publishDate;
    @JsonFormat(pattern = "yyyy-MM-dd")
    private Date endDate;
    private String publisher;

    public Announcement(String title, String content, int type, Date publishDate, Date endDate, String publisher) {
        this.title = title;
        this.content = content;
        this.type = type;
        this.publishDate = publishDate;
        this.endDate = endDate;
        this.publisher = publisher;
    }

    public Announcement() {
    }
}
