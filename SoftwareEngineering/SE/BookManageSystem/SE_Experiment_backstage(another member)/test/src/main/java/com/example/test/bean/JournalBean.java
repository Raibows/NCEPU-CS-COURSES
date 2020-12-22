package com.example.test.bean;

public class JournalBean {

    private String no;
    private String journalName;
    private String startYear;
    private String period;
    private String description;

    public void setNo(String no) {
        this.no = no;
    }

    public void setJournalName(String journalName) {
        this.journalName = journalName;
    }

    public void setStartYear(String startYear) {
        this.startYear = startYear;
    }

    public void setPeriod(String period) {
        this.period = period;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getNo() {
        return no;
    }

    public String getJournalName() {
        return journalName;
    }

    public String getStartYear() {
        return startYear;
    }

    public String getPeriod() {
        return period;
    }

    public String getDescription() {
        return description;
    }
}
