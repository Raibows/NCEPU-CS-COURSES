<template>
  <div>
    <el-dialog
      :visible.sync="modifyVisible"
      title="修改期刊"
    >
      <el-form ref="form" :model="form" :rules="rules" label-width="80px">
        <el-form-item label="编号" prop="no">
          <el-input v-model="form.no" style="width: 30%" :disabled="isDisable" />
        </el-form-item>
        <el-form-item label="期刊名" prop="journalName">
          <el-input v-model="form.journalName" style="width: 30%" :disabled="isDisable" />
        </el-form-item>
        <el-form-item label="期刊类型" prop="period">
          <el-select v-model="form.period" placeholder="请选择期刊类型">
            <el-option label="年刊" value="年刊" />
            <el-option label="月刊" value="月刊" />
            <el-option label="周刊" value="周刊" />
            <el-option label="季刊" value="季刊" />
          </el-select>
        </el-form-item>
        <el-form-item label="日期" prop="startYear">
          <el-col :span="11">
            <el-date-picker v-model="form.startYear" type="date" placeholder="选择日期" style="width: 100%;" :disabled="isDisable" />
          </el-col>
          <el-col class="line" :span="2" />
        </el-form-item>
        <el-form-item label="描述" prop="description">
          <el-input v-model="form.description" type="textarea" :rows="6" />
        </el-form-item>
        <el-form-item>
          <el-button v-if="isAdd==true" type="primary" @click="onAdd">添加</el-button>
          <el-button v-if="isAdd==false" type="primary" @click="onSubmit">修改</el-button>
          <el-button @click="cancel">取消</el-button>
        </el-form-item>
      </el-form>
    </el-dialog>
  </div>
</template>

<script>
import { updateJournal } from '../../../api/periodical'
import { addJournal } from '../../../api/periodical'

export default {
  name: 'Modify',
  data() {
    return {
      modifyVisible: false,
      isAdd: false,
      isDisable: true,
      form: {
        no: '',
        journalName: '',
        startYear: '',
        period: '',
        description: ''
      },
      rules: {
        no: [{ required: true, message: '请输入编号', trigger: 'blur' }],
        journalName: [{ required: true, message: '请输入期刊名', trigger: 'blur' }],
        startYear: [{ required: true, message: '请输入日期', trigger: 'blur' }],
        period: [{ required: true, message: '请输入期刊类型', trigger: 'blur' }],
        description: [{ required: true, message: '请输入描述', trigger: 'blur' }]
      }
    }
  },
  watch: {
    'modifyVisible': function(value) {
      if (!value) {
        this.$refs['form'].resetFields()
        this.$parent.search('')
      }
    }
  },
  methods: {
    update() {
      this.$refs['form'].validate((valid) => {
        if (valid) {
          updateJournal({ no: this.form.no, description: this.form.description, period: this.form.period }).then(
            response => {
              this.$parent.search('')
              this.modifyVisible = false
              this.$message({
                type: 'success',
                message: response.msg
              })
            })
        }
      })
    },
    add() {
      this.$refs['form'].validate((valid) => {
        if (valid) {
          if (this.form.period === '年刊') {
            console.log(23)
            this.form.startYear = this.form.startYear.getFullYear()
          } else if (this.form.period === '月刊') {
            this.form.startYear = this.form.startYear.getFullYear() + '-' + this.form.startYear.getMonth()
          } else if (this.form.period === '周刊') {
            this.form.startYear = this.form.startYear.getFullYear() + '-' + this.form.startYear.getMonth()
          } else {
            this.form.startYear = this.form.startYear.getFullYear() + '-' + this.form.startYear.getMonth() + '-' + this.form.startYear.getDay()
          }
          console.log(this.form.startYear)
          addJournal({
            no: this.form.no,
            journalName: this.form.journalName,
            startYear: this.form.startYear,
            period: this.form.period,
            description: this.form.description
          }).then(response => {
            this.$parent.search('')
            this.modifyVisible = false
            this.$message({
              type: 'success',
              message: response.msg
            })
          })
        }
      })
    },
    onSubmit() {
      this.update()
    },
    onAdd() {
      this.add()
    },
    cancel() {
      this.modifyVisible = false
    }
  }
}
</script>

<style scoped>

</style>
