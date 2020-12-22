package com.example.test.servicelmpl;

import com.example.test.bean.JournalBean;
import com.example.test.bean.JournalSubscribeInfo;
import com.example.test.mapper.JournalMapper;
import com.example.test.service.JournalService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class JournalServiceImpl implements JournalService {

    @Autowired
    private JournalMapper journalMapper;

    @Override
    public List<JournalBean> SearchJournal(String period) {
        return journalMapper.SearchJournal(period);
    }

    @Override
    public boolean AddJournal(String no, String journalName, String startYear, String period, String description) {
        return journalMapper.AddJournal(no,journalName,startYear,period,description);
    }

    @Override
    public boolean DeleteJournal(String no) {
        return journalMapper.DeleteJournal(no);

    }


    @Override
    public boolean ModifyJournal(String no, String description,String period) {
        return journalMapper.ModifyJournal(no,description,period);
    }

    @Override
    public boolean JournalSubscibe(String journalNo, String stuId, String journalName, String period, String description) {
        return journalMapper.JournalSubscibe(journalNo,stuId,journalName,period,description);
    }


    @Override
    public boolean JournalCancel(String journalNo, String stuId) {
        return journalMapper.JournalCancel(journalNo,stuId);
    }

    @Override
    public List<JournalSubscribeInfo> SearchSubscribe(String stuId) {
        return journalMapper.SearchSubscribe(stuId);
    }
}
