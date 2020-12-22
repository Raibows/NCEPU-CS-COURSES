<template>
  <div>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="6">
        <el-input v-model="searchWord" placeholder="请输入期刊类型（支持模糊搜索）" class="input-with-select">
          <el-button slot="append" icon="el-icon-search" @click="searchPeriod" />
        </el-input>
      </el-col>
      <el-col :span="2" :offset="1">
        <el-button type="primary" round @click="addForm({})">添加期刊</el-button>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="18" :offset="3" style="margin-top: 20px;">
        <el-table
          :data="tableData"
          border
          style="width: 100%"
        >
          <el-table-column
            fixed
            prop="no"
            label="编号"
            width="150"
          />
          <el-table-column
            prop="journalName"
            label="期刊名"
            width="120"
          />
          <el-table-column
            prop="startYear"
            label="日期"
            width="120"
          />
          <el-table-column
            prop="period"
            label="期刊类型"
            width="120"
          />
          <el-table-column
            show-overflow-tooltip
            prop="description"
            label="描述"
            width="300"
          />
          <el-table-column
            fixed="right"
            label="操作"
            width="180"
          >
            <template slot-scope="scope">
              <el-button type="primary" size="small" @click="showForm(scope.row)">修改</el-button>
              <el-button type="danger" size="small" @click="deleteJournal(scope.row)">删除</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-col>
    </el-row>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="8">
        <el-pagination
          :current-page="currentPage"
          :page-sizes="[5, 10, 20]"
          :page-size="pageSize"
          layout="total, sizes, prev, pager, next, jumper"
          :total="total"
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
        />
      </el-col>
    </el-row>
    <modifyForm ref="modifyForm" />
  </div>
</template>

<script>
import modifyForm from '../modify/modifyForm.vue'
import { searchJournal, deleteJournal } from '../../../api/periodical'

export default {
  name: 'PeriodicalModify',
  components: { modifyForm },
  data() {
    return {
      tableData: [
        {
          no: '11',
          period: '年刊',
          journalName: '啊',
          description: '就这？',
          startYear: '1985'
        }
      ],
      searchWord: '',
      pageSize: 5,
      currentPage: 1,
      total: 0
    }
  },
  computed: {

  },
  created() {
    this.search('')
  },
  methods: {
    search(keyword) {
      searchJournal({
        period: keyword, pageNum: this.currentPage, pageSize: this.pageSize
      }).then(response => {
        this.tableData = response.data.list,
        this.pageSize = response.data.size,
        this.currentPage = response.data.pageNum,
        this.total = response.data.total,
        console.log(this.tableData[0].description)
      })
    },
    searchPeriod() {
      this.search(this.searchWord)
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.search('')
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.search('')
    },
    showForm(row) {
      this.$refs.modifyForm.modifyVisible = true
      this.$refs.modifyForm.isDisable = true
      this.$refs.modifyForm.isAdd = false
      this.$refs.modifyForm.form = row
    },
    addForm(row) {
      this.$refs.modifyForm.modifyVisible = true
      this.$refs.modifyForm.isAdd = true
      this.$refs.modifyForm.isDisable = false
      this.$refs.modifyForm.form = row
    },
    deleteJournal(row) {
      this.$confirm('将删除此期刊, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        deleteJournal({ no: row.no }).then(response => {
          this.search('')
          this.$message({
            type: 'success',
            message: response.msg
          })
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除'
        })
      })
    }
  }

}
</script>

<style lang="scss" scoped>

</style>
